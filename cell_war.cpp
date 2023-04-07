// 세포전쟁 게임
#include <iostream>
#include <string>
#include <time.h>
using namespace std;
class Cell;
void Death(Cell &c, int team); // Health가 0이하인 세포의 메모리를 반환하는 함수.
class Cell
{
    string name;
    int Attack;
    int Defense;
    int Health;
    int Team;       // 팀번호
    Cell *next;     // 같은팀에서 다음 번호의 Cell
    Cell *previous; // 같은팀에서 전 번호의 Cell
public:
    Cell(string name = "name"); // 생성자 : 초기 이름 name으로 생성. 각 능력치 랜덤, 팀0, next와 previous NULL
    Cell operator+(Cell &op2);  // 능력치 합을 위한 연산자 중복
    void fuse(Cell &c)
    {
        *this = *this + c;
        Death(c, c.Show_Team());
    }                                                   // Cell을 합치고 Death함수로 c메모리 반환
    void Attack_(Cell &c) { c.Attacked(this->Attack); } // 공격할때 함수->상대의 공격 받을때 함수
    void info();                                        // 정보 출력
    void Attacked(int Attack);                          // 공격 받을때 함수
    void Set_Team(int Team) { this->Team = Team; }      // 팀 지정
    int Show_Team() { return this->Team; }              // 팀 반환
    void Set_Name(string name, int n)
    {
        name.append(to_string(n));
        this->name = name;
    }                                                  // 이름 지정
    string Get_Name() { return this->name; }           // 이름 반환
    Cell *add(Cell *p);                                // 팀의 마지막 순서에 새로운 Cell추가
    void back(Cell *p);                                // 전 번호의 Cell을 previous에 입력
    Cell *Get_Next() { return this->next; }            // 다음 Cell주소 반환
    void Reset_Next(Cell *next) { this->next = next; } // 다음 Cell주소 입력
    Cell *Get_previous() { return this->previous; }    // 이전 Cell주소 반환
    int Get_Defense() { return this->Defense; }        // 방어력 반환
    int Get_Attack() { return this->Attack; }          // 공격력 반환
};
Cell::Cell(string name)
{ // 생성자 : 초기 이름 name으로 생성. 각 능력치 랜덤, 팀0, next와 previous NULL
    this->name = name;
    this->Attack = (rand() % 30) + 1;
    this->Defense = (rand() % 30) + 1;
    this->Health = (rand() % 30) + 1;
    this->Team = 0;
    this->next = NULL;
    this->previous = NULL;
}
Cell Cell::operator+(Cell &op2)
{ // 능력치 합을 위한 연산자 중복
    this->name.append(" + ");
    this->name.append(op2.name);
    this->Attack += op2.Attack;
    if (this->Attack > 100)
    {
        this->Attack = 100;
    }
    this->Defense += op2.Defense;
    if (this->Defense > 100)
    {
        this->Defense = 100;
    }
    this->Health += op2.Health;
    if (this->Health > 100)
    {
        this->Health = 100;
    }
    return *this;
}
void Cell::info()
{               // 정보 출력
    int n = 10; // 정보 출력에 장식으로 쓸 =의 갯수를 위한 과정
    if (this->Defense == 100)
        n += 3;
    else if (this->Defense >= 10)
        n += 2;
    else if (this->Attack == 100 || this->Health == 100)
        n += 2;
    else
        n += 1;
    int length = this->name.length() + 7;
    if (length > n)
    {
        n = length;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "=";
    }
    cout << endl;
    cout << "Name : " << this->name << endl;
    cout << "Attack : " << this->Attack << endl;
    cout << "Defense : " << this->Defense << endl;
    cout << "Health : " << this->Health << endl;
    cout << "Team : " << this->Team << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "=";
    }
    cout << endl;
}
void Cell::Attacked(int Attack)
{ // 공격 받을때 함수:데미지 만큼 자신의 체력을 줄이는 함수. 체력이 0이되면 Death함수로 메모리 반환
    int Damage = Attack - this->Defense;
    if (Damage < 0)
        Damage = 0;
    this->Health = this->Health - Damage;
    if (this->Health < 0 || this->Health == 0)
    {
        Death(*this, this->Show_Team());
        return;
    }
}
Cell *Cell::add(Cell *p)
{ // 팀의 마지막 순서에 새로운 Cell추가
    this->next = p;
    return p;
}
void Cell::back(Cell *p)
{ // 전 번호의 Cell을 previous에 입력
    this->previous = p;
}
int team1_life = 10;     // 팀-1의 남은 세포갯수
int team2_life = 10;     // 팀-2의 남은 세포갯수
int sign_startDeath = 0; // 각 팀의 처음 세포가 죽으면 Death함수로 값이 변경되고 main함수에서 팀의 처음 주소를 바꾸고 메모리 반환을 위한 변수
void Death(Cell &c, int team)
{ // Health가 0이하인 세포의 메모리를 반환하는 함수.
    Cell *p;
    p = c.Get_previous();
    if (p == NULL)
    { // 만약 팀의 처음 Cell이면 sign_startDeath의 값을 바꿔 main함수에서 이를 감지해 팀의 처음을 다음 Cell로 바꾸고 메모리를 반환함.
        sign_startDeath = 1;
    }
    else
    {
        p->Reset_Next(c.Get_Next());
        if (c.Get_Next() == NULL)
            ; // c가 마지막 세포였을경우 back함수 안하고 메모리 반환
        else
            c.Get_Next()->back(p);
        delete &c;
    }
    if (team == 1)
    { // Cell이 죽으면 각 팀의 남은 세포갯수를 줄임.
        team1_life--;
    }
    else if (team == 2)
        team2_life--;
}
int main()
{
    srand((unsigned)time(NULL));
    Cell *team1Start = NULL; // 팀-1의 처음시작 세포
    Cell *team1Last;
    Cell *back;
    int start;
    cout << "*******************************************************************************************************************" << endl;
    cout << "O규칙O\n"
         << "각 팀은 랜덤으로 생성된 10개의 세포를 가지고 한턴마다 번갈아가면서 행동을 할 수있습니다.\n";
    cout << "***각 세포 지정 시 세포의 번호를 이용하여 지정해야 합니다.***\n"
         << endl;
    cout << "1)공격은 자신 팀의 세포를 하나 지정하고 상대 팀의 세포를 하나 지정하면" << endl;
    cout << "자신 팀의 세포의 Attack-상대 팀의 세포의 Defense의 수치만큼 상대 팀의 세포의 Health가 차감됩니다.\n"
         << "Health가 0이하가 된 세포는 죽어서 소멸합니다." << endl;
    cout << "소멸한 세포의 번호는 다음 번호의 세포가 한칸씩 당겨져 채웁니다.\n"
         << "Attack-Defense가 음수가 되어도 회복이 되지는 않습니다.\n"
         << endl;
    cout << "2)합성은 자신 팀의 세포 중에 기초가 될 세포 하나와 재료가 될 세포 하나를 선택하면\n 기초가 되는 세포에게 재료가 된 세포의 능력치가 더해집니다." << endl;
    cout << "재료가 된 세포는 소멸되며 마찬가지로 다음 번호의 세포가 한칸씩 당겨 번호를 채웁니다.\n"
         << endl;
    cout << "3)정보보기는 양 팀의 남은 세포의 명단을 볼 수있습니다.\n*정보보기는 턴을 소모하지 않으며 그대로 해당 팀이 이어서 턴을 가지게 됩니다.*" << endl;
    cout << "각각의 세포는 생성될때 랜덤으로 1~30사이로 능력치들이 정해지며 모든 능력치는 합성으로 최대 100까지 증가 가능합니다." << endl;
    cout << "***승리 조건***\n상대의 세포를 모두 소멸시킵니다.\n자신의 어떤 세포의 Defense가 최대치인 100이 됩니다." << endl;
    cout << "자신의 어떤 세포 하나의 Defense가 상대 팀 세포 전체의 Attack합보다 커집니다." << endl;
    cout << "*******************************************************************************************************************" << endl;
    cout << "규칙을 모두 읽으셨다면 321이라고 입력하십시오. 입력하시면 Cell war가 시작됩니다.\n"; // 규칙 설명, 확인하면 시작.
    while (true)
    {
        cout << ">>";
        cin >> start;
        if (start == 321)
            break;
        else
            cout << "틀렸습니다. 다시 입력하세요." << endl;
    }
    team1Start = new Cell();
    if (team1Start == NULL)
    { // 동적할당 실패시 메모리 반환 후 종료
        printf("동적 할당 실패\n");
        delete team1Start;
        return 0;
    }
    team1Last = team1Start;
    for (int i = 0; i < 9; i++)
    {
        back = team1Last;
        team1Last = team1Last->add(new Cell());
        team1Last->back(back);
        if (team1Last == NULL)
        { // 동적할당 실패시 메모리 반환 후 종료
            printf("동적 할당 실패\n");
            Cell *q;
            while (team1Start != NULL)
            {
                q = team1Start->Get_Next();
                delete team1Start;
                team1Start = q;
            }
            return 0;
        }
    }
    Cell *p1 = team1Start;
    for (int i = 1; p1 != NULL; i++)
    { // 이름과 팀 설정
        p1->Set_Name("team1_", i);
        p1->Set_Team(1);
        p1 = p1->Get_Next();
    }
    Cell *team2Start = NULL; // 팀-2의 처음 시작 세포
    Cell *team2Last;
    team2Start = new Cell();
    if (team2Start == NULL)
    { // 동적할당 실패시 메모리 반환 후 종료
        printf("동적 할당 실패\n");
        Cell *q;
        while (team1Start != NULL)
        {
            q = team1Start->Get_Next();
            delete team1Start;
            team1Start = q;
        }
        delete team2Start;
        return 0;
    }
    team2Last = team2Start;
    for (int i = 0; i < 9; i++)
    {
        back = team2Last;
        team2Last = team2Last->add(new Cell());
        team2Last->back(back);
        if (team2Last == NULL)
        { // 동적할당 실패시 메모리 반환 후 종료
            printf("동적 할당 실패\n");
            Cell *q;
            while (team1Start != NULL)
            {
                q = team1Start->Get_Next();
                delete team1Start;
                team1Start = q;
            }
            while (team2Start != NULL)
            {
                q = team2Start->Get_Next();
                delete team2Start;
                team2Start = q;
            }
            return 0;
        }
    }
    Cell *p2 = team2Start;
    for (int i = 1; p2 != NULL; i++)
    { // 이름과 팀 설정
        p2->Set_Name("team2_", i);
        p2->Set_Team(2);
        p2 = p2->Get_Next();
    }
    // 각팀명단출력
    cout << "*****팀-1의 명단*****" << endl;
    p1 = team1Start;
    int num = 1;
    while (p1 != NULL)
    {
        cout << "\n세포 번호 : " << num++ << endl;
        p1->info();
        p1 = p1->Get_Next();
    }
    cout << "*********************\n"
         << endl;
    cout << "*****팀-2의 명단*****" << endl;
    p2 = team2Start;
    num = 1;
    while (p2 != NULL)
    {
        cout << "\n세포 번호 : " << num++ << endl;
        p2->info();
        p2 = p2->Get_Next();
    }
    cout << "*********************\n"
         << endl;
    int n;
    int menu;
    int choice1;
    int choice2;
    n = (rand() % 2) + 1; // 선공 누가할지 랜덤
    cout << "위는 각 팀의 명단입니다. 확인해 주십시오." << endl;
    cout << "(선공은 랜덤으로 정해집니다.)\n"
         << endl;
    cout << "팀-" << n << "이 선공입니다." << endl;
    cout << endl;
    while (true)
    { // Cell war끝날 때 까지 반복. Cell War 끝날 때 return 0;로 종료됨
        while (true)
        {
            cout << "팀-" << n << " 무엇을 하시겠습니까?\n"
                 << endl;
            cout << "1)공격  2)합성  3)정보 보기\n"
                 << endl;
            cin >> menu;
            if (menu == 1 || menu == 2 || menu == 3) // 메뉴의 1, 2, 3이외의 수는 다시 입력받음
                break;
            else
            {
                cout << "해당 숫자만 다시 입력해 주세요." << endl;
            }
        }
        switch (menu)
        {
        case 1: // 공격에 해당
            while (true)
            {
                cout << "공격할 본인 팀의 세포의 번호를 선택해 주세요." << endl;
                cin >> choice1;
                cout << "공격 목표의 번호를 선택해 주세요." << endl;
                cin >> choice2;
                if (n == 1)
                {
                    if ((choice1 < (team1_life + 1)) && (choice1 > 0))
                    { // 세포의 번호가 아닌수 입력시 다시 입력받음
                        if ((choice2 < (team2_life + 1)) && (choice2 > 0))
                            break;
                        else
                            cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                    }
                    else
                        cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                }
                else
                {
                    if ((choice1 < (team2_life + 1)) && (choice1 > 0))
                    {
                        if ((choice2 < (team1_life + 1)) && (choice2 > 0))
                            break;
                        else
                            cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                    }
                    else
                        cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                }
            }
            if (n == 1)
            { // 팀-1의 턴일때
                p1 = team1Start;
                p2 = team2Start;
                for (int i = 1; i < choice1; i++)
                {
                    p1 = p1->Get_Next();
                }
                for (int i = 1; i < choice2; i++)
                {
                    p2 = p2->Get_Next();
                }
                cout << "*********************" << endl;
                cout << "\n|" << p1->Get_Name() << "| ->Attack-> |" << p2->Get_Name() << "|\n"
                     << endl;
                int a = team2_life;
                p1->Attack_(*p2); // 공격함수
                if (sign_startDeath == 1)
                { // Death함수에서 첫째 세포가 죽은 신호를 받으면 팀의 시작 세포의 명칭을 다음 세포에게 넘겨주고 메모리 반환
                    Cell *d = team2Start;
                    if (team2Start->Get_Next() == NULL)
                        ; // 지금 세포가 마지막일시 바로 메모리 반환
                    else
                    {
                        team2Start = team2Start->Get_Next();
                        team2Start->back(NULL);
                    }
                    delete d;
                    sign_startDeath = 0;
                }
                cout << "******공격 결과******\n"
                     << endl;
                if (a != team2_life)
                { // 세포가 죽어서 갯수가 다를때
                    cout << "팀-2의 " << choice2 << "번의 세포가 공격을 받아 소멸되었습니다.\n"
                         << "해당번호 뒷 번호 부터 한칸씩 당겨집니다.\n"
                         << endl;
                }
                else
                {
                    cout << "\n세포 번호 : " << choice2 << endl;
                    p2->info();
                    cout << endl;
                }
                cout << "*********************\n"
                     << endl;
                n++; // 팀-2의 턴으로 바꿈
            }
            else
            { // 팀-2의 턴일때
                p1 = team1Start;
                p2 = team2Start;
                for (int i = 1; i < choice1; i++)
                {
                    p2 = p2->Get_Next();
                }
                for (int i = 1; i < choice2; i++)
                {
                    p1 = p1->Get_Next();
                }
                cout << "*********************" << endl;
                cout << "\n|" << p2->Get_Name() << "| ->Attack-> |" << p1->Get_Name() << "|\n"
                     << endl;
                int a = team1_life;
                p2->Attack_(*p1); // 공격함수
                if (sign_startDeath == 1)
                { // Death함수에서 첫째 세포가 죽은 신호를 받으면 팀의 시작 세포의 명칭을 다음 세포에게 넘겨주고 메모리 반환
                    Cell *d = team1Start;
                    if (team1Start->Get_Next() == NULL)
                        ; // 지금 세포가 마지막일시 바로 메모리 반환
                    else
                    {
                        team1Start = team1Start->Get_Next();
                        team1Start->back(NULL);
                    }
                    delete d;
                    sign_startDeath = 0;
                }
                cout << "******공격 결과******\n"
                     << endl;
                if (a != team1_life)
                {
                    cout << "팀-1의 " << choice2 << "번의 세포가 공격을 받아 소멸되었습니다.\n"
                         << "해당번호 뒷 번호 부터 한칸씩 당겨집니다.\n"
                         << endl;
                }
                else
                {
                    cout << "\n세포 번호 : " << choice2 << endl;
                    p1->info();
                    cout << endl;
                }
                cout << "*********************\n"
                     << endl;
                n--; // 팀-1의 턴으로 바꿈
            }
            break;
        case 2: // 합성
            while (true)
            {
                cout << "본인 팀의 세포 중 합성의 기초가 될 세포의 번호를 선택해 주세요." << endl;
                cin >> choice1;
                cout << "합성 재료로 사용할 본인 팀의 세포의 번호를 선택해 주세요." << endl;
                cin >> choice2;
                if (n == 1)
                {
                    if (choice1 != choice2) // 같은 세포 입력시 다시 입력받음
                        if ((choice1 < (team1_life + 1)) && choice1 > 0)
                        { // 세포의 번호가 아닌수 입력시 다시 입력받음
                            if ((choice2 < (team1_life + 1)) && choice2 > 0)
                                break;
                            else
                                cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                        }
                        else
                            cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                    else
                        cout << "재료는 다른 세포를 선택해 주세요.\n"
                             << "다시 선택해 주세요" << endl;
                }
                else
                {
                    if (choice1 != choice2)
                        if ((choice1 < (team2_life + 1)) && choice1 > 0)
                        {
                            if ((choice2 < (team2_life + 1)) && choice2 > 0)
                                break;
                            else
                                cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                        }
                        else
                            cout << "해당 번호가 없습니다. 다시 선택해 주세요." << endl;
                    else
                        cout << "재료는 다른 세포를 선택해 주세요.\n"
                             << "다시 선택해 주세요" << endl;
                }
            }
            if (n == 1)
            { // 팀-1일때
                p1 = team1Start;
                p2 = team1Start;
                for (int i = 1; i < choice1; i++)
                {
                    p1 = p1->Get_Next();
                }
                for (int i = 1; i < choice2; i++)
                {
                    p2 = p2->Get_Next();
                }
                cout << "*********************" << endl;
                cout << "\n|" << p2->Get_Name() << "| ->Fuse-> |" << p1->Get_Name() << "|\n"
                     << endl;
                p1->fuse(*p2);
                if (sign_startDeath == 1)
                { // 합성으로 세포 소멸시에도 마찬가지로 메모리 반환
                    Cell *d = team1Start;
                    if (team1Start->Get_Next() == NULL)
                        ;
                    else
                    {
                        team1Start = team1Start->Get_Next();
                        team1Start->back(NULL);
                    }
                    delete d;
                    sign_startDeath = 0;
                }
                cout << "******합성 결과******" << endl;
                cout << "\n세포 번호 : " << choice1 << endl;
                p1->info();
                cout << "팀-1의 " << choice2 << "번째 세포가 합성에 의해 사라졌습니다.\n"
                     << "해당번호 뒷 번호 부터 한칸씩 당겨집니다.\n"
                     << endl;
                cout << "*********************\n"
                     << endl;
                if (p1->Get_Defense() == 100)
                { // 합성으로 방어력이 최대가 됬을때 Cell War끝
                    cout << "팀-1의 " << choice2 << "번째 세포의 Defense가 최대치가 되어\n죽지 않기 때문에 Cell War가 종료됩니다." << endl;
                    cout << "팀-1의 승리입니다." << endl;
                    cout << "*****살아남은 팀-1의 명단*****" << endl;
                    p1 = team1Start;
                    num = 1;
                    while (p1 != NULL)
                    {
                        cout << "\n세포 번호 : " << num++ << endl;
                        p1->info();
                        p1 = p1->Get_Next();
                    }
                    cout << "***********************\n"
                         << endl;
                    cout << "팀-1의 " << choice2 << "번째 세포의 Defense가 최대치가 되어\n죽지 않기 때문에 Cell War가 종료됩니다." << endl; // 명단이 길시 위에 보기 힘들기때문에
                    cout << "팀-1의 승리입니다." << endl;                                                                                   // 한번 더 출력
                    Cell *q;
                    while (team1Start != NULL)
                    { // 진팀도 메모리할당한게 남아있으므로 메모리 반환 후 종료
                        q = team1Start->Get_Next();
                        delete team1Start;
                        team1Start = q;
                    }
                    while (team2Start != NULL)
                    {
                        q = team2Start->Get_Next();
                        delete team2Start;
                        team2Start = q;
                    }
                    return 0;
                }
                n++; // 팀-2의 턴으로 바꿈
            }
            else
            { // 팀-2일때
                p1 = team2Start;
                p2 = team2Start;
                for (int i = 1; i < choice1; i++)
                {
                    p1 = p1->Get_Next();
                }
                for (int i = 1; i < choice2; i++)
                {
                    p2 = p2->Get_Next();
                }
                cout << "*********************" << endl;
                cout << "\n|" << p2->Get_Name() << "| ->Fuse-> |" << p1->Get_Name() << "|\n"
                     << endl;
                p1->fuse(*p2);
                if (sign_startDeath == 1)
                {
                    Cell *d = team2Start;
                    if (team2Start->Get_Next() == NULL)
                        ;
                    else
                    {
                        team2Start = team2Start->Get_Next();
                        team2Start->back(NULL);
                    }
                    delete d;
                    sign_startDeath = 0;
                }
                cout << "******합성 결과******" << endl;
                cout << "\n세포 번호 : " << choice1 << endl;
                p1->info();
                cout << "팀-2의 " << choice2 << "번째 세포가 합성에 의해 사라졌습니다.\n"
                     << "해당번호 뒷 번호 부터 한칸씩 당겨집니다.\n"
                     << endl;
                cout << "*********************\n"
                     << endl;
                if (p1->Get_Defense() == 100)
                {
                    cout << "팀-2의 " << choice2 << "번째 세포의 Defense가 최대치가 되어\n죽지 않기 때문에 Cell War가 종료됩니다." << endl;
                    cout << "팀-2의 승리입니다." << endl;
                    cout << "*****살아남은 팀-2의 명단*****" << endl;
                    p1 = team1Start;
                    num = 1;
                    while (p1 != NULL)
                    {
                        cout << "\n세포 번호 : " << num++ << endl;
                        p1->info();
                        p1 = p1->Get_Next();
                    }
                    cout << "***********************\n"
                         << endl;
                    cout << "팀-2의 " << choice2 << "번째 세포의 Defense가 최대치가 되어\n죽지 않기 때문에 Cell War가 종료됩니다." << endl;
                    cout << "팀-2의 승리입니다." << endl;
                    Cell *q;
                    while (team1Start != NULL)
                    { // 진팀도 메모리할당한게 남아있으므로 메모리 반환 후 종료
                        q = team1Start->Get_Next();
                        delete team1Start;
                        team1Start = q;
                    }
                    while (team2Start != NULL)
                    {
                        q = team2Start->Get_Next();
                        delete team2Start;
                        team2Start = q;
                    }
                    return 0;
                }
                n--; // 팀-1의 턴으로 바꿈
            }
            break;
        case 3: // 정보 보기
            cout << "*****남은 팀-1의 명단*****" << endl;
            p1 = team1Start;
            num = 1;
            while (p1 != NULL)
            {
                cout << "\n세포 번호 : " << num++ << endl;
                p1->info();
                p1 = p1->Get_Next();
            }
            cout << "********************\n"
                 << endl;
            cout << "*****남은 팀-2의 명단*****" << endl;
            p2 = team2Start;
            num = 1;
            while (p2 != NULL)
            {
                cout << "\n세포 번호 : " << num++ << endl;
                p2->info();
                p2 = p2->Get_Next();
            }
            cout << "********************\n"
                 << endl;
        }
        if (team1_life == 0 || team2_life == 0)
        { // 어느 한팀의 남은 세포가 0일때 Cell War종료
            cout << "Cell War가 종료되었습니다." << endl;
            if (team1_life == 0)
            {
                cout << "팀-2의 승리입니다." << endl;
                cout << "*****살아남은 팀-2의 명단*****" << endl;
                p2 = team2Start;
                num = 1;
                while (p2 != NULL)
                {
                    cout << "\n세포 번호 : " << num++ << endl;
                    p2->info();
                    p2 = p2->Get_Next();
                }
                cout << "***********************\n"
                     << endl;
                cout << "Cell War가 종료되었습니다." << endl;
                cout << "팀-2의 승리입니다." << endl;
                Cell *q;
                while (team2Start != NULL)
                { // 이긴팀 남은 메모리 반환 후 종료
                    q = team2Start->Get_Next();
                    delete team2Start;
                    team2Start = q;
                }
                return 0;
            }
            else
            {
                cout << "팀-1의 승리입니다." << endl;
                cout << "*****살아남은 팀-1의 명단*****" << endl;
                p1 = team1Start;
                num = 1;
                while (p1 != NULL)
                {
                    cout << "\n세포 번호 : " << num++ << endl;
                    p1->info();
                    p1 = p1->Get_Next();
                }
                cout << "***********************\n"
                     << endl;
                cout << "Cell War가 종료되었습니다." << endl;
                cout << "팀-1의 승리입니다." << endl;
                Cell *q;
                while (team1Start != NULL)
                { // 이긴팀 메모리 반환 후 종료
                    q = team1Start->Get_Next();
                    delete team1Start;
                    team1Start = q;
                }
                return 0;
            }
        }
        p1 = team1Start;
        p2 = team2Start;
        int defense = p1->Get_Defense();
        p1 = p1->Get_Next();
        while (p1 != NULL)
        {
            if (p1->Get_Defense() > defense)
                defense = p1->Get_Defense();
            p1 = p1->Get_Next();
        }
        int attack = 0;
        while (p2 != NULL)
        {
            attack += p2->Get_Attack();
            p2 = p2->Get_Next();
        }
        if (defense > attack)
        { // 팀-1의 방어력 가장높은 세포의 방어력이 팀-2의 모든 세포의 공격력을 더한 것 보다 클때 팀-1의 승리
            cout << "Cell War가 종료되었습니다." << endl;
            cout << "팀-1의 승리입니다." << endl;
            cout << "*****살아남은 팀-1의 명단*****" << endl;
            p1 = team1Start;
            num = 1;
            while (p1 != NULL)
            {
                cout << "\n세포 번호 : " << num++ << endl;
                p1->info();
                p1 = p1->Get_Next();
            }
            cout << "***********************\n"
                 << endl;
            cout << "팀-2의 모든 세포의 공격력을 합해도\n팀-1의 가장 방어력이 높은 세포의 방어력보다 낮아\n데미지를 줄 수 없기때문에\nCell War가 종료되었습니다." << endl;
            cout << "팀-1의 승리입니다." << endl;
            Cell *q;
            while (team1Start != NULL)
            { // 이긴팀 메모리 반환 후 종료
                q = team1Start->Get_Next();
                delete team1Start;
                team1Start = q;
            }
            while (team2Start != NULL)
            {
                q = team2Start->Get_Next();
                delete team2Start;
                team2Start = q;
            }
            return 0;
        }
        p1 = team1Start;
        p2 = team2Start;
        defense = p2->Get_Defense();
        p2 = p2->Get_Next();
        while (p2 != NULL)
        {
            if (p2->Get_Defense() > defense)
                defense = p2->Get_Defense();
            p2 = p2->Get_Next();
        }
        attack = 0;
        while (p1 != NULL)
        {
            attack += p1->Get_Attack();
            p1 = p1->Get_Next();
        }
        if (defense > attack)
        { // 팀-2의 방어력 가장높은 세포의 방어력이 팀-1의 모든 세포의 공격력을 더한 것 보다 클때 팀-2의 승리
            cout << "Cell War가 종료되었습니다." << endl;
            cout << "팀-1의 승리입니다." << endl;
            cout << "*****살아남은 팀-2의 명단*****" << endl;
            p2 = team2Start;
            num = 1;
            while (p2 != NULL)
            {
                cout << "\n세포 번호 : " << num++ << endl;
                p2->info();
                p2 = p2->Get_Next();
            }
            cout << "***********************\n"
                 << endl;
            cout << "팀-1의 모든 세포의 공격력을 합해도\n팀-2의 가장 방어력이 높은 세포의 방어력보다 낮아\n데미지를 줄 수 없기때문에\nCell War가 종료되었습니다." << endl;
            cout << "팀-2의 승리입니다." << endl;
            Cell *q;
            while (team1Start != NULL)
            { // 메모리 반환 후 종료
                q = team1Start->Get_Next();
                delete team1Start;
                team1Start = q;
            }
            while (team2Start != NULL)
            {
                q = team2Start->Get_Next();
                delete team2Start;
                team2Start = q;
            }
            return 0;
        }
        cout << "팀-1의 남은 세포 : " << team1_life << endl;
        /*p1 = team1Start;//남은 세포 이름만 출력되는것. 이것을 출력시 각 행동의 결과가 위로 올라가 한번에 보기 힘들게되어 주석처리
        num = 1;
        while (p1 != NULL) {
        cout << "   |No." << num++ << " = " << p1->Get_Name() << "|" << endl;
        p1 = p1->Get_Next();
        }
        cout << endl;*/
        cout << "팀-2의 남은 세포 : " << team2_life << endl;
        /*p2 = team2Start;
        num = 1;
        while (p2 != NULL) {
        cout << "   |No." << num++ << " = " << p2->Get_Name() << "|" << endl;
        p2 = p2->Get_Next();
        }*/
        cout << endl;
    }
}