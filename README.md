#  Mr. FILE

- 'Motion Recognition' demo using FILE transmission
- 2019 수원대학교 정보보호학과 2학년 자바 프로젝트
- 팀내 맡은 역할: virtual mouse 기능 구현

<br>
</br>

# ✅ 개요

 - 아이디어 상의 중 마우스를 쥘 수 없는 환경에 있거나, 손가락을 자유자재로 움직일 수 없는 사람들이 컴퓨터를 사용할 때 불편할 수 있다는 문제점에 대해 생각을 하게 됨.

 - 모션 인식 기술로서 컴퓨터와 상호작용을 하게 되면 언급한 내용을 개선시킬 수 있을 것이라 예상해보면서 기획을 함.

<br>
</br>

# ✅ 목적

 앞에서 언급했던 문제점을 해결하기 위해 모션 인식 기술을 기반으로 다양한 기능을 추가 함으로서

마우스나 터치패드 없이 입력 장치로서의 기능을 다 하는 것

<br>
</br>

# ✅ 개발 일정
![image](https://user-images.githubusercontent.com/48430781/113152053-afe5d680-9270-11eb-971a-a36980ff3bbc.png)

<br>
</br>

# ✅ 기능

 1) File Drag & Drop

    - 방향별로 존재하는 Adapter에 각각 다른 사용자를 설정한다.

    - Drag & Drop을 통하여 파일을 잡고, Adapter로 Drop 시키면 파일이 전송된다.

 2) TCP를 이용한 파일전송

    - 클라이언트에서 파일을 Drag & Drop 하게 되면, Drag된 파일의 절대경로를 인식하여 보낼 파일의 이름을 알려준다.

    - 서버에서 파일을 전송받아 바탕화면에 띄운다.

3) 모션 인식 Interface (GitHub 소스코드 응용)

    - 노트북의 카메라를 통하여 사용자의 모션을 입력한다.

    - 손가락 관절 하나하나와 손바닥의 움직임을 체크한다.

    - 손가락으로 잡는 듯한 모션을 위해 엄지와 검지를 인식한다.

    - 클릭하는 모션을 잡는 것처럼 표현하기 위해 두 손가락의 각도를 인식한다. 

    - 일정 각도보다 작아질 경우에 손가락을 모은 것으로 인식하며, 마우스 클릭과 클릭한 상태를 유지한다. 

    - 일정 각도보다 커질 경우에 클릭 상태를 해제한다.

 <br>
</br>

# 🎸 개발 언어와 도구

 1) UI : Java (IntelliJ)

 2) server & client : Window API 소켓 프로그래밍을 이용, C++ (Visual Studio)

 3) motion recognition : python , open cv와 연동 (Pycharm)

<br>
</br>

# ✅ 버전 세팅

- Python (3.9)
- numpy (1.26.4)
- app (0.0.1)
- wxPython (4.2.1)

- opencv 설치 (4.9.0.80)
```
python -m pip install --upgrade pip
python install opencv-python
```

- pynput 설치 (1.7.6)
```
pip install pynput
```

<br>
</br>

# ✅ UI 소개
![image](https://user-images.githubusercontent.com/48430781/113152058-b2483080-9270-11eb-8141-6425e9d20775.png)

<br>
</br>

# ✅ 견본이미지
![image](https://user-images.githubusercontent.com/48430781/113153663-49fa4e80-9272-11eb-8b84-77ce2c3d09b7.png)
![image](https://user-images.githubusercontent.com/48430781/113153401-043d8600-9272-11eb-86a4-ce55c235b3f7.png)
 
