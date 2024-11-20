import ctypes
import signal
import sys

# 加载动态链接库
mylib = ctypes.CDLL('./example.so')  # 根据实际路径更新

# 定义C++中的数据结构 robotArm1
class RobotArm1(ctypes.Structure):
    _fields_ = [("pos", ctypes.c_float * 6)]

# 设置函数参数和返回类型
#mylib.move_to_pos.argtypes = [ctypes.c_int]  # 参数类型为int
#mylib.move_to_pos.restype = None  # 返回类型为None

joint_movement = mylib.joint_movement
joint_movement.restype = None
joint_movement.argtypes = [ctypes.POINTER(ctypes.c_float)]

pos_movement = mylib.joint_movement
pos_movement.restype = None
pos_movement.argtypes = [ctypes.POINTER(ctypes.c_float)]

# 定义键盘中断处理函数
def signal_handler(sig, frame):
    mylib.brake()
    print("shou daoxinhao tuichu!")
    mylib.logout()
    print('Exiting the program')
    sys.exit(0)

# 注册键盘中断处理函数
signal.signal(signal.SIGINT, signal_handler)

# 创建一个实例
TH = RobotArm1()

#TH.pos[0]=4.5
#TH.pos[1]= 316.30
#TH.pos[2]=312.43
#TH.pos[3]=2.08
#TH.pos[4]=-1.27
#TH.pos[5]=-1.98

#float arr1[6] = {2.2,  -0.68,  2.22,  1.48,  1.56, 1.32};
#TH.j[0]=2.2
#TH.j[1]=-0.68
#TH.j[2]=2.22
#TH.j[3]=1.48
#TH.j[4]=1.56
#TH.j[5]=1.32
#arr1 = {2.2,  -0.68,  2.22,  1.48,  1.56, 1.32};

arr1 = (ctypes.c_float * 6)(2.2, -0.68, 2.22, 1.48, 1.56, 1.32)#角度值

arr_pos=(ctypes.c_float * 6)(-7.74078 ,328.817 ,223.455 ,-2.02142 ,-3.13438, 0.0495672);#pos值
# 调用C++函数
mylib.ip_address.restype=ctypes.c_char_p
ip=mylib.ip_address().decode('latin-1')
print(ip)
mylib.login()

mylib.mechanical_arm_origin()
mode=2
#mylib.move_to_pos(mode)
#mylib.move_to_joint(mode)
while True:
    mylib.joint_movement(arr1)
    print('pos1=',TH.pos[1])

    mylib.mechanical_arm_origin()
    #print('j1=',TH.j[1])
    mylib.pos_movement(arr_pos)
    mylib.mechanical_arm_origin()
    
mylib.logout()
print('qqeqeq')



