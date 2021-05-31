# A13528608
import matplotlib.pyplot as plt
import numpy as np
import math


def predict(x_t, u_t1, alpha):
    """ Sample odometry motion model.
    Args:
        x [x, y, theta]: robot position
        u_t1 [rot1, rot2, trans]: odometry
        a [a1, a2, a3, a4]: error
    Returns:
        [new_x, new_y, new_t]
    """
    d_hat_r1 = u_t1[0] + \
        np.random.normal(0, alpha[0]*abs(u_t1[0]) + alpha[1]*u_t1[2])
    d_hat_r2 = u_t1[1] + \
        np.random.normal(0, alpha[0]*abs(u_t1[1]) + alpha[1]*u_t1[2])
    d_hat_theta = u_t1[2] + np.random.normal(
        0, alpha[2]*u_t1[2] + alpha[3] * (abs(u_t1[0])+abs(u_t1[1])))
    new_x = x_t[0] + d_hat_theta * math.cos(x_t[2] + d_hat_r1)
    new_y = x_t[1] + d_hat_theta * math.sin(x_t[2] + d_hat_r1)
    new_theta = x_t[2] + d_hat_r1 + d_hat_r2
    return np.array([new_x, new_y, new_theta])


def question2():
    x_t = [2, 4, 0]
    u_t = [np.pi / 2, 0, 1]
    alpha = [0.1, 0.1, 0.01, 0.01]

    num_samples = 5000
    new_x = []
    for i in range(0, num_samples):
        new_x.append(predict(x_t, u_t, alpha))

    new_x = np.array(new_x)
    plt.plot(x_t[0], x_t[1], "go")
    plt.plot(new_x[:, 0], new_x[:, 1], "ro")
    plt.show()


def predict_next_pos(x, y, theta, v_l, v_r, t, l, w_r):
    """ forward kinematics of 4 wheel robot

    Args:
        x, y, theta (float): initial position/angle of the robot
        v_l/r (float): speed of left/right wheel
        t (float): driving time
        l (float): distance between wheel
        w_r (float): wheel radius

    Returns:
        x_1, y_1, theta_1 (float): new robot configuration
    """

    #
    if v_l == v_r:
        return x + v_l * t * np.cos(theta), y + v_l * t * np.sin(theta), theta

    # center of curvature
    r_c = l / 2.0 * (v_l + v_r) / (v_r - v_l)
    x_c = x - r_c * np.sin(theta)
    y_c = x - r_c * np.cos(theta)

    new_theta = theta + (v_r - v_l) / l * t
    new_x = x_c + np.sin(new_theta) * r_c
    new_y = y_c - np.cos(new_theta) * r_c

    return new_x, new_y, new_theta


def question3():
    x, y, theta = predict_next_pos(0, 0, np.pi, 1, 1, 3, 0.5, 100)
    print("new poistion x: %f, y: %f, theta: %f" % (x, y, theta))


question3()
