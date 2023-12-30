# code-optimization
### 실행 환경
- Linux (Ubuntu 20.04)
- gcc 7.5.0

### 실행 방법
```Shell
$ gcc -Wall -pg code.c -o code -lpthread
$ ./code argv[1] argv[2]
$ gprof code gmon.out > result.txt
```

### 최적화 함수 목록
- Bubble sort
- Selection sort
- Insert sort
- Quick sort
- Monte carlo simulation
- atoi
- main

### 상세 정보
더 자세한 정보는 [이곳](https://minyakk.tistory.com/47#%EC%B5%9C%EC%A0%81%ED%99%94%20(Optimization)-1)에서 확인하실 수 있습니다.