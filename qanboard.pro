CONFIG += c++11

# Import the C++ code
include(app/app_src.pri)

test {
    message(Building Qanboard unit tests...)

    include(test/test.pri)
}
else {
    message(Building Qanboard app...)

    include(app/app.pri)
    include(deployment.pri)
}
