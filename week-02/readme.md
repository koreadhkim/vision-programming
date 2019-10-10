## task 01. 다음을 프로그래밍으로 구현하시오.

<img src="./task-01/assets/input1.jpg" width="40%">

1. 위 영상을 Mat img1 = imread( ) 함수를 이용하여 영상을 읽어 오시오.
2. 또 다른 영상을 저장하기 위해 Mat img2;로 하고, 이것은 칼라(3채널)로 저장하기 위해 선언하시오.
3. 위의 grayscale영상에서 원은 초록색으로, 마름모는 파랑색으로, 삼각형은 빨강색으로, 직사각형은 노랑색
으로 만들어 화면에 띄우시오. 이때, 위1과 비교하여 제대로 되었는지 확인하시오.

### 결과
<img src="./task-01/assets/output_02.jpg" width="70%"> <br>
먼저, threshold_value를 찾기위해 trackbar 를 이용하여 값을 찾는다. 찾은 값들을 이용하여 main_02.cpp를 실행 시킨다.<br>
<img src="./task-01/assets/output_03.jpg" width="50%"> <br>



