void InitScreen(void);
void InitData(void);                            // ���� ���� ���� (Ȯ�� ����)
void Run(void);
void CompareWords(void);                        // ���ڿ� ��
void ProcessInput(int key);                     // �Է�
void DrawWord(int i);                           // ȭ�鿡 ��Ÿ�� i��° �ܾ� ���
void EraseWord(int i);                          // ȭ�鿡 ��Ÿ�� i��° �ܾ� �����
void UpdateScore(void);                         // ���� ī����
void UpdateFailCount(void);						// ���� ���� ī��Ƽ
void InitWord(int i);							//�ܾ� ������ġ ǥ�� �� �ܾ� ���� �ʱ�ȭ
void NextStage(void);                           //8���� �Ǹ� �����ܰ� ���� ������ 5���̵Ǹ� fail
void StageScreen(void);                         // ��ũ�� ui
void StartGame(void);							// ���� ����