#!/usr/bin/env python
#-- coding:utf-8 --

#=============================================
# 함께 사용되는 각종 파이썬 패키지들의 import 선언부
#=============================================
import pygame
import numpy as np
import math
import rospy
from xycar_msgs.msg import xycar_motor

#=============================================
# 모터 토픽을 발행할 것임을 선언
#=============================================
motor_pub = rospy.Publisher('xycar_motor', xycar_motor, queue_size=1)
xycar_msg = xycar_motor()

#=============================================
# 프로그램에서 사용할 변수, 저장공간 선언부
#=============================================
rx, ry = [], []

#=============================================
# 프로그램에서 사용할 상수 선언부
#=============================================
AR = (1142, 62) # AR 태그의 위치
P_ENTRY = (1036, 162) # 주차라인 진입 시점의 좌표
P_END = (1129, 69) # 주차라인 끝의 좌표

#=============================================
# 모터 토픽을 발행하는 함수
# 입력으로 받은 angle과 speed 값을
# 모터 토픽에 옮겨 담은 후에 토픽을 발행함.
#=============================================
def drive(angle, speed):
    xycar_msg.angle = int(angle)
    xycar_msg.speed = int(speed)
    motor_pub.publish(xycar_msg)

#=============================================
# 경로를 생성하는 함수
# 차량의 시작위치 sx, sy, 시작각도 syaw
# 최대가속도 max_acceleration, 단위시간 dt 를 전달받고
# 경로를 리스트를 생성하여 반환한다.
#=============================================
def planning(sx, sy, syaw, max_acceleration, dt):
    global rx, ry, i

    print(sx,sy,syaw)
    i=0 # tracking 부분에서의 i 값을 새롭게 0으로 맞춰준다.

    if sx >= P_ENTRY[0] and syaw == 180: # 차량의 현재 x좌표가 도착지점의 x값보다 크고(차량이 도착지점보다 오른쪽에 위치)
                                         # 위를 바라보고 있을 때.
        linear_length = 300              # 후진 할 직선거리 길이 설정
        via_points_x = np.full(100,sx)   # via point(방문 점) x 좌표값 설정
        via_points_y = np.linspace(sy,sy+linear_length,len(via_points_x)) # via point(방문 점) y 좌표값 설정

        # via_point 부터 도착지점까지의 전진 경로 생성
        fx, fy = getPathUsingCartasianPolynomials(sx,sy+linear_length,syaw,P_ENTRY[0],P_ENTRY[1],-45)

        # 후진 경로와 전진경로 결합
        rx = np.append(via_points_x, fx)
        ry = np.append(via_points_y,fy)

    elif sx>=P_ENTRY[0] and syaw ==270: # 차량의 현재 x좌표가 도착지점의 x값보다 크고(차량이 도착지점보다 오른쪽에 위치)
                                        # 오른쪽을 바라보고 있을 때.
        linear_length=300               # 후진 직선거리 길이 설정
        via_points_y = np.full(100,sy)  # via point(방문 점) x 좌표값 설정
        via_points_x = np.linspace(sx,sx-linear_length,len(via_points_y)) # via point(방문 점) y 좌표값 설정

        # via_point 부터 도착지점까지의 전진 경로 생성
        fx, fy = getPathUsingCartasianPolynomials(sx-linear_length,sy,syaw,P_ENTRY[0],P_ENTRY[1],-45)

        # 후진 경로와 전진경로 결합
        rx = np.append(via_points_x, fx)
        ry = np.append(via_points_y,fy)

    elif sx>=P_ENTRY[0] and syaw != 180 and syaw !=270: # 현재 차량의 x좌표가 도착지점의 x값보다 크고 현재 각도가 180 혹은 270이 아닐 때
                                                        # 후진 경로를 만들어 내는 수식이 syaw가 180이나 270일 때와 달라져야 한다.
        via_x = P_ENTRY[0]-200                          # 후진해서 도달 할 x 좌표 설정
        via_y = getAboutY(sx,sy,syaw,via_x)             # 후진해서 도달 할 y좌표 설정
        via_points_x = np.arange(via_x,sx,step=5)       # sx부터 via_x까지의 x 좌표 배열 생성
        via_points_y = getAboutY(sx,sy,syaw,via_points_x)  # 현재 기울기에 맞는 sy부터 via_y까지의 좌표배열 설정

        via_points_x = via_points_x[::-1]     # 현재 배열 역순 설정
        via_points_y = via_points_y[::-1]     # 현재 배열 역순 설정

        # via_point 부터 도착지점까지의 전진 경로 생성
        fx, fy = getPathUsingCartasianPolynomials(via_x,via_y,syaw,P_ENTRY[0],P_ENTRY[1],-45)

        # 후진 경로와 전진경로 결합
        rx = np.append(via_points_x, fx)
        ry = np.append(via_points_y,fy)

    elif sx<P_ENTRY[0] and sy>P_ENTRY[1]: # 현재 차량의 x좌표가 도착지점의 x값보다 작고 y좌표가 도착지점의 y좌표보다 클 때.
                                          # 시뮬레이터 상으로 도착지점을 기준으로 왼쪽 하단에 있을 경우 -> 후진할 필요 X
        # 현재 좌표부터 도착지점까지의 경로 생성
        rx, ry = getPathUsingCartasianPolynomials(sx,sy,syaw,P_ENTRY[0],P_ENTRY[1],-45)

    return rx, ry

def getAboutY(sx,sy,syaw,via_x): # 현재 기울기에 맞는 y값을 반환해주는 함수. 상수, 배열 둘 다 가능
    return -np.tan(math.radians(syaw))*(via_x - sx) + sy

# 전진 경로 생성 함수. 후진이 필요한 경로를 생성하지 못한다.
# Two parking manoeuvres planned via cubic Cartesian polynomials 알고리즘 사용
def getPathUsingCartasianPolynomials(sx,sy,syaw,fx,fy,fyaw):

    # tan 계산을 위한 syaw 조정
    if syaw == 270:
        syaw = 0
    elif syaw == 180:
        syaw = -70
    else:
        syaw = 180-syaw

    k = 900 # 곡률 파라미터

    # 알고리즘의 alpha, beta 파라미터 값 설정
    alpha = np.array([k*np.cos(math.radians(fyaw)) - 3*fx, \
             k*np.sin(math.radians(fyaw)) - 3*fy])
    beta = np.array([k*np.cos(math.radians(syaw)) + 3*sx, \
             k*np.sin(math.radians(syaw)) + 3*sy])

    s = np.linspace(0, 1, 100)
    ones = np.ones(len(s))

    # 경로 생성
    rx = (s**3)*fx - ((s-ones)**3)*sx + alpha[0]*(s-ones)*s**2 + beta[0]*s*(s-ones)**2
    ry = (s**3)*fy - ((s-ones)**3)*sy + alpha[1]*(s-ones)*s**2 + beta[1]*s*(s-ones)**2

    return rx,ry

#=============================================
# 생성된 경로를 따라가는 함수
# 파이게임 screen, 현재위치 x,y 현재각도, yaw
# 현재속도 velocity, 최대가속도 max_acceleration 단위시간 dt 를 전달받고
# 각도와 속도를 결정하여 주행한다.
#=============================================
def tracking(screen, x, y, yaw, velocity, max_acceleration, dt):
    global rx, ry, i
    '''
    경로에 생성된 점을 한칸 씩 밀어가며 차량이 그 점을 따라가도록 구현하였다.
    '''
    # 목표 지점 좌표 설정
    goal_x = (P_ENTRY[0]+P_END[0]) // 2
    goal_y = (P_ENTRY[1]+P_END[1]) // 2

    # 경로의 마지막에 목표지점 추가
    rx = np.append(rx,goal_x)
    ry = np.append(ry,goal_y)
    dist_goal = np.sqrt((goal_x-x)**2 + (goal_y-y)**2)


    # rx와 ry의 인덱스 i 값을 증가시키며 점을 따라가야 하므로 배열 index를 초과하지 않도록 설정
    if i>=len(rx):
        i = len(rx)

    # 현재 좌표와 바로 다음지점의 점 사이의 각도를 게산
    # 90도 같은 특수 상황을 배재하기 위한 처리도 포함되어 있다.
    if np.abs(rx[i]-x)==0:   # 다음 좌표의 x와 현재 x좌표가 같으면 goal_yaw를 90으로 수동설정한다.
                             # tan를 사용하기에 부적합하기 때문이다.
        goal_yaw = 0

    # x 값의 차이가 0은 아니지만 정말 미묘할 경우 파이썬에서 그냥 0으로 처리해 버린다. 이를 막기 위한 수동 조절이다.
    if np.abs(rx[i]-x)<0.00001:  # 다음 좌표의 x와 현재 x좌표가 미묘하게 차이가 나면 goal_yaw를 수동설정한다.
        if rx[i]>x:              # 다음좌표의 x좌표가 더 크면
            goal_yaw = 88        # 좀 더 확실한 회전 운동을 위해 goal_yaw를 88로 한다.
        else:                    # 다음좌표의 x좌표가 더 작으면
            goal_yaw = 92        # 좀 더 확실한 회전 운동을 위해 goal_yaw를 92로 한다.
    else:
        # 일반적인 상황에서 다음좌표와의 각도 차이 계산
        goal_yaw = math.degrees(-math.atan2(ry[i]-y, rx[i]-x))

    # 가끔 처음의 goal_yaw값이 비어있는 경우가 생기는 데 이를 처리하기 위한 구문이다.
    if np.isnan(goal_yaw):
        goal_yaw = yaw
    else:
        pass

    # 현재 각도와 goal_yaw간의 각도 차이 게산
    # 이를 통해 구한 angle은 그대로 회전운동의 가중치로 들어가게 된다.
    diff_yaw = abs(goal_yaw - yaw)

    if goal_yaw >=0 and goal_yaw >= yaw:
        angle = -diff_yaw
    elif goal_yaw >=0 and goal_yaw < yaw:
        angle = diff_yaw
    elif goal_yaw < 0:
        angle = 180-diff_yaw

    # 직전만으로 다음 좌표로 향할 수 있으면 angle은 0에 가까울 것이고
    # 각도차이가 많이 나서 큰 회전운동을 해야한다면 angle 값은 커진다.
    # 50*angle을 drive함수의 인수로 이용할 예정인데 그 때의 angle이고
    # 이는 다음포인트와 연관있는 가중치를 의미하기도 한다.
    angle = math.radians(angle)

    # 다음 목표지점까지의 거리 계산
    dist_next = np.sqrt((rx[i]-x)**2 + (ry[i]-y)**2)

    if dist_next<=100:  # 다음 목표지점까지의 거리가 100 pixel 사이면 i 값을 증가시킨다.
        i+=1

    # 현재 x좌표와 y좌표 다음 x,y와의 차이 값 계산
    diff_x = rx[i] - x
    diff_y = ry[i] - y

    # 차이에 따른 velocity directioon 결정
    # 처음 세 경우는 차량이 후진을 해야한다.
    # 마지막 경우는 차량이 전진을 해야한다.
    if diff_x<=0 and diff_y>=0:
        a = -1
    elif diff_x==0 and diff_y>0:
        a = -1
    elif diff_x<0 and diff_y==0:
        a = -1
    else:
        a = 1

    if dist_goal<=0.8:  # 목표지점과의 거리차이가 0.8 이내면 도착이라 판단
        drive(0,0)
        print(f'도착: {x:.2f},{y:.2f}')
        return ;
    else:               # 주행
        drive(50*angle, a*50)
        print(f'{i} : {x:.2f},{y:.2f} >>-->> {rx[i]:.2f},{ry[i]:.2f}')
        print(f's:{yaw:.2f}, g:{goal_yaw:.2f}, diff:{diff_yaw:.2f}, a:{angle:.2f}\n')
