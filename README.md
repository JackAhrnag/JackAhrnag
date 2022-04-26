# 목차

<br>
<ol>
<li>네트워크 유량</li>
<li>포드-풀커슨 알고리즘</li>
<li>입력값 및 결과값</li>
<li>조금 더 알아볼 게 있을까</li>
</ol>
<br>

---

<br>

# 네트워크 유량

<br>

코로나로 인해 사람들은 집에 틀어박혀 무엇을 할까? 코로나 때문에 대학에 가기 힘들 때 우리는 무엇을 이용하여 수업을 들을까? 하물며 지금 이 글을 쓰고 읽는 것은 무엇 덕분일까? 그렇다 **인터넷**, 그리고 그것을 이어주는 **네트워크**이다. 2022년 4월 26일 기준, 네이버 국어사전에는 '랜(LAN)이나 모뎀 따위의 통신 설비를 갖춘 컴퓨터를 이용하여 서로 연결시켜 주는 조직이나 체계.'라 등록되어있는 이 네트워크는 현 우리 사회에서 때놓을래야 때놓을 수 없는 것이 되었다.

<br>

그렇다면 우리는 여기서 한 가지 예를 들어보자. **네트워크를 이용하여 용량이 아주 큰 파일을 다운로드하는 중이라고 했을 때, 어떻게 하면 빨리 다운받을 수 있을까?** 사실 네트워크도 도로와 같다. 한 곳에서 다른 한 곳으로 바로 이어주는 길이 있는가 하면, 우회해서 가는 길도 있는 법이다. 우리는 시작지점에서 도착지점까지 빠르게 가는 방법을 알고 있다. 그렇다 그리디 알고리즘과 분할정복 알고리즘을 배운 우리라면 알고있다. 최단경로를 찾는 것이다. 빨리 다운받는 방법도 위와 비슷하나 조금은 다르다. **시작지점에서 도착지점까지 가장 많은 용량을 한 번에 보낼 수 있는 경로를(또는 방법을)찾는 것이다.** 그리고 우리는 **한 경로만을 사용하는 것이 아닌 여러 경로를 한 번에 이용할 것이다.** 최단경로로만 1초에 1MB를 보내는 것보다, 좀 먼길을 돌아서 간다 해도 여러 경로를 이용하여 한 번에 10MB를 보내는 것이 이득이지 않을까.

<br>

본격적인 설명 이전에 우선 용어를 짚어보고 넘어가자.

<br>

* Source: 시작점
* Sink: 도착점
* Capacity: 용량 (간선에서 소화 가능한 최대 양 or 값)
* Flow: 유량 (간선에서 용량을 점유하고 있는, 사용하고있는 양 or 값)
* c(a, b): 정점 a 에서 b로, 소화 가능한(남은) 용량 값
* f(a, b): 정점 a 에서 b로, 사용하고 있는(쓴) 유량 값

<br>

네트워크 유량의 특징은 여러 곳을 보며 공부한 결과 크게 3가지 라고 한다.

<br>

**첫째로,** 각 간선에 흐르는 유량은 그 간선의 용량을 넘을 수 없다. 예를 들어 우리가 A집에서 B집으로 10MB의 속도로 파일을 보낸다고 가정했을 때, A와 B집 사이의 용량(Capacity)이 8MB라면, 10MB라는 유량이 용량을 초과했으므로 이는 불가능하다.

<br>

**둘째로,** 한 정점을 기중으로 보았을 때, 해당 정점에서 들어오는 유량의 총합은 나가는 유량의 총합과 같아야 한다. 예를 들어 A와 B가 C에 각각 10MB의 유량으로 파일을 보내고 이를 C가 D에 보낸다면 C의 유량은 20MB가 되어야 한다. 하지만 여기서 만약 C에서 D로 가는 용량이 20MB 미만이라면 이는 불가능하다.

<br>

**셋째로,** 네트워크 유량 알고리즘의 핵심 아이디어로 역이 있다고 한다. A에서 B로 유량이 보내질 때, 'B에서는 A로 음수의 유량을 보내고 있고 용량은 0이다.'라고 생각하면 편하다. 대부분의 블로그에서 이 개념을 설명할 때 '우선 이런 것이 있다는 걸 알고 넘아간 후에, 알고리즘과 그림을 통해 이해해보자'라고 한다. 나 또한 이를 글로 설명하기에는 어렵기에 아래에 그림을 통하여 이해한 내용을 어느정도 설명할 예정이다.

<br>

**자, 지금부터 한 번 본격적으로 들어가보도록 하자.**

<br>

![유량 네트워크1](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fb4kZxc%2FbtqYn5WR7aI%2FI1zyItfMIFy6XWcAXeYbmk%2Fimg.png)

<br>

위와 같은 네트워크가 있다고 가정해보자. 만약 우리가 하나의 경로(또는 최단경로)만을 이용했을 때 보낼 수 있는 유량은 (0, 1)과 (2, 3)의 용량 때문에 1이 될 수밖에 없다. 하지만 여러 경로를 이용한다면 우리는 이보다 더 많은 유량을 보낼 수 있게 된다.

<br>

![유량 네트워크2](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbymNat%2FbtqYoY4eSMs%2FtWaHylzGE7BAJe6ecVl9Xk%2Fimg.png)

<br>

이와 같이 유량을 보내는 경로를 우리는 증가 경로(augmenting path)라고 부른다. 또한 간선의 용량과 유량의 차이를 잔여 용량(residual capacity)이라고 부른다 한다. 예시로 위의 그림에서 (1, 3)의 용량은 2, 유량은 1이다. 그렇다면 현 상태에서 (1, 3)의 잔여 용량은 몇일까? 1이라는 것을 쉽게 생각할 수 있을 것이다.

<br>

계속해서 다음으로 넘어가보도록 하자.

<br>

![유량 네트워크3](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FF1Cvm%2FbtqYj9Z4OZG%2FrVf9hNYFDZo5Bif8Gkbx70%2Fimg.png)

<br>

최단 경로만을 사용하지 않고 여러 증가 경로를 이용하여 총 유량을 증가시키는 것은 듣기에는 쉽고 좋아보이나 위와 같은 문제가 발생할 수 있다. 경로를 잘못 짚어 버리면, 우리는 2라는 유량을 보낼 수 있음에도 1라는 유량을 보낼 수 밖에 없게 된다. 이를 해결하기 위해서 우리는 역간선과 포드-풀커슨 알고리즘을 이용할 것이다.

<br>

---

<br>

# 포드-풀커슨 알고리즘

<br>

이 알고리즘의 동작 원리는 다음과 같다.

<br>

**첫째로,** 시작점에서 도착점으로 가는 증가 경로를 하나 정한다. 이 때, 모든 간선에 아직 잔여 용량이 남아있어야 한다.

<br>

**둘째로,** 증가 경로 중에 특정한 하나의 간선을 찾는다. 이 간선은 용량을 c, 유량을 f라 할 때,  **'c(1, 2) - f(1, 2) > 0'** 값이 최소인 간선이다. 이 최소값을 F라 해보자.

<br>

**셋째로,** 경로상의 모든 간선에 F만큼의 유량을 추가한다. 즉 시작점에서 도착점까지의 경로를 따라서 F만큼의 유량을 새로 더하는 것이다. 여기서 위의 네트워크 유량의 특징 중 세번째에 따라 역간선 또한 행해야 한다. 즉 역방향으로 흐르는 음의 유량 또한 흘려줘야 한다.

<br>

위의 과정을 더 이상 증가 경로가 없을 때 까지 반복한다고 한다. 이번에는 그림과 같이 설명을 해보자.

<br>

![포드-풀커슨 알고리즘1](https://blogfiles.pstatic.net/20160904_41/kks227_1472996430633MaJ6t_PNG/6.png?type=w3)

<br>

위와 같은 네트워크가 있다는 가정을 해보자. 우리는 S에서 T까지 파일을 보내야하는대, 어떻게 하면 한 번에 많은 유량을 보낼 수 있을까? 여기서 우리는 포드-풀커슨 알고리즘을 이용할 것이다.

<br>

![포드-풀커슨 알고리즘2](https://blogfiles.pstatic.net/20160904_250/kks227_1472996430856YIrj5_PNG/7.png?type=w3)

<br>

우선 첫째로, 시작점에서 도착점으로 가는 증가 경로를 하나 고른다. 여기서는 [S-A-E-T]를 골랐다.  
그리고 둘째로, 'c(1, 2) - f(1, 2) > 0'가 최소인 값을 찾는다. 여기서는 3과 5가 보이는대, 3이 5보다 작기 때문에 이 값은 3이다.  
셋째로, [S-A-E-T]경로에는 3의 유량이 흐르게 된다.  
그리고 이 과정을 반복해보자.

<br>

![포드-풀커슨 알고리즘3](https://blogfiles.pstatic.net/20160904_52/kks227_1472996431432SvRQe_PNG/8.png?type=w3)

<br>

[S-B-E-T]라는 경로를 골랐고, 최소값은 2이며, [S-B-E-T]경로에는 2의 유량이 흐른다. 여기서 [E-P]는 이전에 3의 유량이 흐르고 있었기 때문에 2가 더해져 총 5의 유량이 흐르게 된다.

<br>

![포드-풀커슨 알고리즘4](https://blogfiles.pstatic.net/20160904_123/kks227_1472996431671Oq1Ew_PNG/9.png?type=w3)

<br>

다음에 [S-C-F-T]라는 경로를 찾았고, 최소값은 4이며, [S-C-F-T]경로에는 4의 유량이 흐른다.

<br>

자, 겉보기에는 더 이상 증가 경로를 찾을 수 없고, [A-D-T]가 남아있다고는 하지만 갈 수 있는 경로의 용량은 남아있지 않다. [T]로 흘러들어오는 유량은 총 9이기 때문에, 우리가 한 번에 최대로 전송할 수 있는 유량은 9이다.

<br>

### 라고 할 수는 없다.

<br>

우리가 지금까지 사용하지 않은 네트워크 유량의 특징은 무엇인가. 그렇다, 네트워크 유량 알고리즘의 핵심 아이디어 **'역간선'** 이다.

<br>

![포드-풀커슨 알고리즘5](https://blogfiles.pstatic.net/20160904_184/kks227_1472996431931YSqwH_PNG/11.png?type=w3)

<br>

네트워크 유량의 특징 세번째를 다시 생각해보자. [A-B]일 때 [B-A]로는 음수의 유량이 흐르고 용량은 0이다. 자, 이와 같은 특징을 위에 그림과 같이 [A-E]간선에 적용시켜보자. [A-E]로는 3의 유량이 흐르기 때문에 [E-A]로는 -3의 유량이 흐르고 용량은 0이다. 새로운 간선을 찾았고 우리는 이를 이용하려 새로은 증가 경로를 찾을 수 있다.

<br>

![포드-풀커슨 알고리즘6](https://blogfiles.pstatic.net/20160904_102/kks227_1472996432172bJOaH_PNG/10.png?type=w3)

<br>

[S-C-F-R-A-D-T]라는 증가 경로를 찾았고, 이의 최소값은 1이기에, 이 경로에 1의 유량이 흐르게 된다. 추가적으로 [A-E]간선에는 반대방향으로 1의 유량이 흐르기에 유량이 1이 줄어들게 된다. 이렇게 되면 [T]에 모이는 총 유량은 10으로 아까의 9보다 1의 유량이 늘어나게 된다.

<br>

포드-풀커슨 알고리즘은 기본적으로 '깊이 우선 탐색'(DFS)으로, DFS의 시간복잡도는 O(V+E)이다. 또한 포드-풀커슨 알고리즘은 문제의 답이 f일 때 최대 f번 반복 될 수 있기에, 포드-풀커슨의 시간복잡도는 최악의 경우  O(V+E)f가 된다. 여기서 대부분의 경우 E가 V보다 크기 때문에 OEf로 표현한다. 

<br>

---

<br>

# 입력값 및 결과값

<br>

예시의 코드는 아래와 같다.

<br>

```
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX_V = 52;
const int INF = 1000000000;

// 정점 문자를 0~51 사이의 번호로 바꿔주는 간단한 함수
inline int CtoI(char c) 
{
	if (c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}

int main() 
{
	int N; // 간선 개수
	int c[MAX_V][MAX_V] = { 0 }; // c[i][j]: i에서 j로 가는 간선의 용량
	int f[MAX_V][MAX_V] = { 0 }; // f[i][j]: i에서 j로 현재 흐르는 유량
	vector<int> adj[MAX_V]; // 인접 리스트

	// 간선 정보 입력받기
	scanf("%d", &N);
	for (int i = 0; i < N; i++) 
	{
		char u, v;
		int w;
		scanf(" %c %c %d", &u, &v, &w);
		u = CtoI(u); v = CtoI(v);
		c[u][v] = c[v][u] += w; // 같은 간선이 여러 번 들어올 수 있으므로 +=
		adj[u].push_back(v);
		adj[v].push_back(u); // 역방향 간선도 추가해줘야 함
	}

	// total: 총 유량, S: 소스, E: 싱크
	int total = 0, S = CtoI('A'), E = CtoI('Z');
	// 증가 경로를 못 찾을 때까지 루프

	while (1) 
	{
		// 증가 경로를 BFS로 찾음
		int prev[MAX_V];

		fill(prev, prev + MAX_V, -1);

		queue<int> Q;
		Q.push(S);

		while (!Q.empty() && prev[E] == -1) 
		{
			int curr = Q.front();
			Q.pop();

			for (int next : adj[curr]) 
			{
				// c[i][j]-f[i][j] > 0: i에서 j로 유량을 흘릴 여유가 남았는가?
				// prev[next] == -1: next 정점을 아직 방문하지 않았는가?
				if (c[curr][next] - f[curr][next] > 0 && prev[next] == -1) {
					Q.push(next);
					prev[next] = curr; // 경로를 기억하기 위해 prev 배열 사용

					if (next == E) break; // 싱크에 도달하면 나옴
				}
			}
		}
		// 싱크로 가는 경로가 더 없으면 루프 탈출
		if (prev[E] == -1) break;

		// 경로상에서 가장 허용치가 낮은 곳을 찾음
		int flow = INF;
		for (int i = E; i != S; i = prev[i])
			flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
		// 찾은 flow만큼 해당 경로에 유량 흘려줌
		for (int i = E; i != S; i = prev[i]) 
		{
			f[prev[i]][i] += flow;
			f[i][prev[i]] -= flow;
		}
		// 총 유량 값 증가
		total += flow;
	}
	// 결과 출력
	printf("%d\n", total);
}
```
















































































