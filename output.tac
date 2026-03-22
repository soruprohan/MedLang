; MedLang Three-Address Code
begin_func Admission
    param "=== Trigonometry Table ===\n"
    t0 = call Observe, 1
    param "Angle(deg) | sin       | cos       | tan\n"
    t1 = call Observe, 1
    param "-----------|-----------|-----------|----------\n"
    t2 = call Observe, 1
    PI = 3.14159
    deg = 0
L0:
    t3 = deg <= 6
    ifnot t3 goto L1
    t4 = deg * 30
    angle_deg = t4
    t5 = angle_deg * PI
    t6 = t5 / 180
    angle_rad = t6
    param angle_rad
    t7 = call Sine, 1
    s = t7
    param angle_rad
    t8 = call Cosine, 1
    c = t8
    param angle_rad
    t9 = call Tangent, 1
    t = t9
    param "%d          | %f  | %f  | %f\n"
    param angle_deg
    param s
    param c
    param t
    t10 = call Observe, 5
    t11 = deg + 1
    deg = t11
    goto L0
L1:
    param "\n=== Blood Pressure Critical Check ===\n"
    t12 = call Observe, 1
    systolic = 155
    diastolic = 95
    param systolic
    param diastolic
    t13 = call IsCritical, 2
    critical = t13
    param "Systolic: %d, Diastolic: %d\n"
    param systolic
    param diastolic
    t14 = call Observe, 3
    ifnot critical goto L2
    param "Status: CRITICAL - immediate attention required\n"
    t15 = call Observe, 1
    goto L3
L2:
    param "Status: Normal\n"
    t16 = call Observe, 1
L3:
end_func
