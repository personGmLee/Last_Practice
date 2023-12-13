void InitScreen(void);
void InitData(void);                            // 아직 내용 없음 (확장 가능)
void Run(void);
void CompareWords(void);                        // 문자열 비교
void ProcessInput(int key);                     // 입력
void DrawWord(int i);                           // 화면에 나타난 i번째 단어 출력
void EraseWord(int i);                          // 화면에 나타난 i번째 단어 지우기
void UpdateScore(void);                         // 점수 카운팅
void UpdateFailCount(void);						// 실패 점수 카운티
void InitWord(int i);							//단어 랜덤위치 표시 및 단어 상태 초기화
void NextStage(void);                           //8점이 되면 다음단계 실패 점수가 5점이되면 fail
void StageScreen(void);                         // 스크린 ui
void StartGame(void);							// 게임 시작