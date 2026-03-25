; MedLang Three-Address Code
begin_func greet
    param "Hello, %s!\n"
    param name
    t0 = call Observe, 2
end_func
begin_func diagnosePatient
    param "Patient : %s\n"
    param patient
    t1 = call Observe, 2
    param "Condition: %s\n"
    param condition
    t2 = call Observe, 2
end_func
begin_func getStatus
    t3 = code == 1
    ifnot t3 goto L0
    return "Critical"
L0:
    t4 = code == 2
    ifnot t4 goto L2
    return "Stable"
L2:
    return "Unknown"
end_func
begin_func Admission
    msg = "String variables work!"
    param "%s\n"
    param msg
    t5 = call Observe, 2
    pname = "Alice"
    param pname
    t6 = call greet, 1
    param "Bob"
    t7 = call greet, 1
    patient = "John Doe"
    condition = "Hypertension"
    param patient
    param condition
    t8 = call diagnosePatient, 2
    code = 1
    param code
    t9 = call getStatus, 1
    status = t9
    param "Status: %s\n"
    param status
    t10 = call Observe, 2
    code2 = 2
    param code2
    t11 = call getStatus, 1
    status2 = t11
    param "Status: %s\n"
    param status2
    t12 = call Observe, 2
end_func
