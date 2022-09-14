# PID 란


**PID 제어기의 일반적인 구조**

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex0.png?raw=true" width="400" height="400"><br>


표준적인 형태의 PID 제어기는 아래의 식과 같이 세개의 항을 더하여 제어값(MV : Manipulated Variable)을 계산하도록 구성이 되어 있다.

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex0.png?raw=true" width="400" height="400"><br>



이 항들은 각각 오차값, 오차값의 적분(integral), 오차값의 미분(derivative)에 비례하기 때문에 비례-적분-미분 제어기 (Proportional–Integral–Derivative controller)라는 명칭을 가진다. 

</br>

* 비례항 : 현재 상태에서의 오차값의 크기에 비례한 제어작용을 한다.
* 적분항 : 정상상태(steady-state) 오차를 없애는 작용을 한다.
* 미분항 : 출력값의 급격한 변화에 제동을 걸어 오버슛(overshoot)을 줄이고 안정성(stability)을 향상시킨다.


</br>

**1) P 제어( 비례항)**

</br>

현재 상태에서의 오차값의 크기에 비례한 제어작용을 한다.

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex1-1.png?raw=true" width="400" height="100"><br>


초기 상태에서 비례항을 적용한 그래프<br> 

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex1.png?raw=true" width="400" height="400"><br>

> Kp 가 높을 떄 : setpoint는 빨리 도달하지만 전제척으로 오차가 크고 시스템이 불안정하다.


</br>

**2) I 제어( 적분항 )**

비례항의 응답곡선에서 비례 시스템은 오차를 제어하기 어려웠다. 적분항은 시간에 걸친 오차의 합을 말하는데 오차가 클 경우 적분항에 의해 시간이 지나면서 오차의 합이 쌓이며 출력은 빠르게 변해 오차를 제거하게 된다.

</br>

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex2-2.png?raw=true" width="400" height="100"><br>

비례항을 거쳐 I제어(적분항)을 적용한 그래프<br>

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex2.png?raw=true" width="400" height="400"><br>

> 전체적으로 setpoint와의 오차가 줄고 시스템이 좀 더 안정화 되었다.

**3) D 제어( 미분항 )**

</br>

미분항은 오차 변화율을 계산해 그 결과를 출력에 더한다. 오차의 변화가 작으면 미분항의 값이 작다.(출력에 영향을 크게 미치지 않는다.) 그러나 오차가 크면 미분항의 값이 커진다.


<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex3-1.png?raw=true" width="400" height="100"><br>


적분항을 거쳐 D제어(미분항)을 적용한 그래프

<img src="https://github.com/alswo471/IOT/blob/main/drone/PID%20%EC%9B%90%EB%A6%AC/images/PIDex3.png?raw=true" width="400" height="100"><br>

적분항에 있던 오차들은 변화율에 따라 제거해줘서 setpoint와 거의 일치하게됨 시스템이 안정화 수준이다.








</br>
</br>
</br>
</br>
</br>
</br>
