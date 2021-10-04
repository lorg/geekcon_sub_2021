try:
    from microbit import *
    import radio
except ImportError:
    pass

GYRO_ERROR_X = 300
GYRO_ERROR_Y = 300
GYRO_U_SIZE = 2


# def gyro2bytes(v):
#     return v.to_bytes(GYRO_U_SIZE, 'big', True)
# def bytes2gyro(a_bytes):
#     return int.from_bytes(a_bytes, 'big', True)
def gyro2bytes(v):
    return str(int(v)).encode('ascii')
    # return v.to_bytes(GYRO_U_SIZE, 'big', True)
def bytes2gyro(a_bytes):
    return int(a_bytes.decode('ascii'))
    # return int.from_bytes(a_bytes, 'big', True)

def display_gyro(a_x, a_y, a_z):
    display.clear()
    if GYRO_ERROR_X < a_x:
        display.set_pixel(4, 2, 9)
    if -GYRO_ERROR_X > a_x:
        display.set_pixel(0, 2, 9)
    if GYRO_ERROR_Y < a_y:
        display.set_pixel(2, 4, 9)
    if -GYRO_ERROR_Y > a_y:
        display.set_pixel(2, 0, 9)
    # display.set_pixel(2, 2, min(0, min(abs(vals[2])/10,9)))


# --- Running Code ---------->>>

def controller():
    radio.config(group=31)
    radio.on()

    while True:
        sleep(100)

        seq = accelerometer.get_values()
        seq = [bytes2gyro(gyro2bytes(x)) for x in seq]
        a_x, a_y, a_z = tuple(seq)
        # display.scroll(a_y)
        # b = gyro2bytes(a_y)
        # a_y = bytes2gyro(b)
        display_gyro(a_x, a_y, a_z)
        radio.send_bytes(gyro2bytes(a_x) + b' ' + gyro2bytes(a_y) + b' ' + gyro2bytes(a_z))


def turn(a_x):
    # Servo control:
    # 50 = ~1 millisecond pulse all right
    # 75 = ~1.5 millisecond pulse center
    # 100 = ~2.0 millisecond pulse all left

    if GYRO_ERROR_X < a_x:
        pin0.write_analog(60) #right
    elif -GYRO_ERROR_X > a_x:
        pin0.write_analog(90) #left
    else:
        pin0.write_analog(75) #center


def move_forward(a_y):
    if GYRO_ERROR_Y < a_y:
        pin1.write_digital(1)
    if -GYRO_ERROR_Y > a_y:
        pin1.write_digital(0)
        
def receiver():
    radio.config(group=31)
    radio.on()
    pin0.set_analog_period(20)

    blat = 50
    while True:
        sleep(10)
        msg_data = radio.receive_bytes()
        if msg_data is None:
            continue

        a_x, a_y, a_z = tuple(bytes2gyro(x) for x in msg_data.split(b' '))
        display_gyro(a_x, a_y, a_z)

        move_forward(a_y)
        turn(a_x)
        # pin0.write_analog(blat)
        blat+=5
        if 100 < blat:
            blat=50


# controller()
receiver()
