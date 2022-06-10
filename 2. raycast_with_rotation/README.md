- [x] 천장과 바닥 부분 색 clear
  - 이전 window의 형태가 window의 background에 같이 출력됨
  - window를 아무리 clear 시켜도 img 자료 자체에 저장해둔 pixel 정도에 값이 들어있기 때문에 img를 print하면 현재 움직임에 따라 갱신되지 않은 부분은 이전의 모습이 그대로 남아있음
  - 현재 수직선에 대해 img draw할 때, start 지점보다 작거나 end 지점보다 큰 index의 경우 검정색으로 채워넣음으로써 갱신시킴
  - 추후 과제 요구사항에 따라 수정 필요
    - ceiling : start보다 작은 index들의 영역
    - floor : end보다 큰 index들의 영역

- [x] x, y 좌표에 대한 고료
  - 삼각함수 공식을 생각할 때의 x, y좌표와 window 상의 좌표가 달라서 그대로 수식을 반영하면 left, right가 반대로 움직였음
  - 이를 반대로 적용시켜서 처리

![화면 기록 2022-06-10 오후 3 32 57](https://user-images.githubusercontent.com/64132798/173007403-d08c098c-6625-4960-9d75-a4b8e08fd70f.gif)
