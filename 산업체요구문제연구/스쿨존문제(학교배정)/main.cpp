// Project : 1차 school
// 작성자 : 심상혁
// Date of first create : 2023.03.20
// Major features:
// -3개의 학교, 10000명의 학생을 한 학교에 최대 3500명을 넘지않도록 배정하기
// -0,0 ~ 999,999의 좌표 상에 학생과 학교가 있다고 가정.
// -학교와 학생사이의 거리의 합이 최소가 되도록 할것.
// Date of last update : 2023.03.23

extern void get_school_position(int school_index, int *posX, int *posY);
extern void get_student_position(int student_index, int *posX, int *posY);
extern void set_student_school(int student_index, int school_index);

void run_contest(void)
{
    struct school // 학교 구조체
    {
        int x;     // 학교 x좌표
        int y;     // 학교 y좌표
        int count; // 학교에 배정된 학생 수
    };
    struct Node // 이동을 위한 연결리스트를 위한 구조체
    {
        int index; // 학생 번호
        int d;     // 해당 학생의 배정된 학교에서 다른 학교로 이동할때 증가하는 거리
        int to;    // 이동 할 학교
        struct Node *next;
    };

    struct Node *shead[3]; // 학교의 학생들이 다른 학교로 갈 때의 정보를 가지는 연결리스트들의 헤드
    shead[0] = 0;          // 0번 학교의 학생들 연결 리스트 헤드
    shead[1] = 0;          // 1번 학교의 "
    shead[2] = 0;          // 2번 학교의 "

    struct school a[3]; // 학교 구조체
    // 학생수 초기화
    a[0].count = 0;
    a[1].count = 0;
    a[2].count = 0;

    for (int i = 0; i < 3; i++)
    {
        get_school_position(i, &a[i].x, &a[i].y); // 학교의 x, y좌표 획득
    }

    int x;           // 학생 x좌표
    int y;           // 학생 y좌표
    int d[3];        // 학생과 학교와 거리 변수
    int d0d1;        // 학생과 0학교와의 거리와 학생과 1학교와의 거리 차(d0-d1의 양수)
    int d1d2;        // 1학교와 2학교 "
    int d2d0;        // 2학교와 0학교 "
    int sequence[3]; // 가장 가까운 학교 순서. sequence[0]이 가장 가까운 학교번호

    int stud[10000];                 // 학생이 배정된 학교 번호를 저장하는 배열(인덱스가 학생번호)
    struct Node student_list[20000]; // 연결리스트를 위한 노드를 생성하기위한 배열
    int slist_count = 0;             // 연결리스트 index를 위한 변수
    struct Node sample;              // 빈 노드

    for (int i = 0; i < 10000; i++) // 10000번 돌면서 학생의 정보를 가져와 구조체에 넣는다
    {
        get_student_position(i, &x, &y); // 학생 좌표 얻기

        d[0] = (a[0].x - x) * (a[0].x - x) + (a[0].y - y) * (a[0].y - y); // 0학교와 거리

        d[1] = (a[1].x - x) * (a[1].x - x) + (a[1].y - y) * (a[1].y - y); // 1학교와 거리

        d[2] = (a[2].x - x) * (a[2].x - x) + (a[2].y - y) * (a[2].y - y); // 2학교와 거리

        // 거리차 구하기
        d0d1 = d[0] - d[1];
        d1d2 = d[1] - d[2];
        d2d0 = d[2] - d[0];
        if (d0d1 < 0) // 음수면 양수로
            d0d1 = -1 * d0d1;
        if (d1d2 < 0)
            d1d2 = -1 * d1d2;
        if (d2d0 < 0)
            d2d0 = -1 * d2d0;

        // 학생과 가까운 학교 찾기
        if (d[0] <= d[1] && d[0] <= d[2]) // 0번 학교가 가장 가까운 경우
        {
            stud[i] = 0;     // 일단 학교 배정 0번으로
            sequence[0] = 0; // 가장 가까운것 0번

            if (d[1] <= d[2]) // 다음으로 1번이 가까운 경우
            {
                sequence[1] = 1; // 2번째로 가까운거 1번
                sequence[2] = 2; // 3번째로 가까운거 2번
            }
            else
            {
                sequence[1] = 2;
                sequence[2] = 1;
            }
            a[0].count++; // 학교의 학생수 증가.
        }
        else if (d[1] <= d[0] && d[1] <= d[2]) // 1번 학교가 가장 가까운 경우
        {
            stud[i] = 1;
            sequence[0] = 1;
            if (d[0] <= d[2])
            {
                sequence[1] = 0;
                sequence[2] = 2;
            }
            else
            {
                sequence[1] = 2;
                sequence[2] = 0;
            }
            a[1].count++;
        }
        else // 2번 학교가 가장 가까운 경우
        {
            stud[i] = 2;
            sequence[0] = 2;
            if (d[0] <= d[1])
            {
                sequence[1] = 0;
                sequence[2] = 1;
            }
            else
            {
                sequence[1] = 1;
                sequence[2] = 0;
            }
            a[2].count++;
        }
        // 연결 리스트에 사용할 노드를 20000개 짜리 배열에서 가져오기
        struct Node *newNode1 = &student_list[slist_count++];
        struct Node *newNode2 = &student_list[slist_count++];

        // 해당 학생의 가장 가까운 학교에서 다른 학교로 이동할 때의 정보
        newNode1->index = i; // 학생인덱스
        newNode2->index = i;
        newNode1->next = 0; // 노드의 다음은 일단 NULL
        newNode2->next = 0;
        newNode1->to = sequence[1]; // 이동할 학교 번호 = 두번째 또는 세번째로 가까운 학교 번호
        newNode2->to = sequence[2];
        newNode1->d = d[sequence[1]] - d[sequence[0]]; // 이동할때 거리 증가량 = 이동할 학교 거리 - 가장 가까운학교 거리
        newNode2->d = d[sequence[2]] - d[sequence[0]];

        // 노드의 d에 따른 순서로 연결리스트 구성 (d가 작은것이 head가 되도록)
        if (shead[stud[i]] == 0) // 가장 가까운 학교 연결리스트 헤드가 NULL인 경우
        {
            newNode1->next = newNode2;
            shead[stud[i]] = newNode1;
        }
        else // 노드가 있는 경우 d의 크기를 비교하여 작은 값이 앞으로 오도록 연결리스트 연결
        {
            if (shead[stud[i]]->d >= newNode1->d)
            {
                if (shead[stud[i]]->d >= newNode2->d)
                {
                    newNode1->next = newNode2;
                    newNode2->next = shead[stud[i]]->next;
                    shead[stud[i]] = newNode1;
                }
                else
                {
                    newNode1->next = shead[stud[i]];
                    shead[stud[i]] = newNode1;
                    struct Node *current = shead[stud[i]];
                    while ((current->next != 0) && (current->next->d < newNode2->d))
                    {
                        current = current->next;
                    }
                    newNode2->next = current->next;
                    current->next = newNode2;
                }
            }
            else
            {
                struct Node *current = shead[stud[i]];
                while ((current->next != 0) && (current->next->d < newNode1->d))
                {
                    current = current->next;
                }
                newNode1->next = current->next;
                current->next = newNode1;
                while ((current->next != 0) && (current->next->d < newNode2->d))
                {
                    current = current->next;
                }
                newNode2->next = current->next;
                current->next = newNode2;
            }
        }
    }

    int max_s; // 학생수가 최대인 학교
    int mid_s; // 학생수가 두번째인 학교
    int min_s; // 학생수가 세번째인 학교

    // 학교 구조체의 count를 비교하여 각 변수에 값을 설정
    if (a[0].count >= a[1].count && a[0].count >= a[2].count)
    {
        max_s = 0;
        if (a[1].count >= a[2].count)
        {
            mid_s = 1;
            min_s = 2;
        }
        else
        {
            mid_s = 2;
            min_s = 1;
        }
    }
    else if (a[1].count >= a[2].count)
    {
        max_s = 1;
        if (a[0].count >= a[2].count)
        {
            mid_s = 0;
            min_s = 2;
        }
        else
        {
            mid_s = 2;
            min_s = 0;
        }
    }
    else
    {
        max_s = 2;
        if (a[0].count >= a[1].count)
        {
            mid_s = 0;
            min_s = 1;
        }
        else
        {
            mid_s = 1;
            min_s = 0;
        }
    }
    // 하나가 3500 초과에 나머지가 둘다 3500 미만인 경우
    // 3500보다 작은거에 넣을 때 연결리스트 수정 필요하다.
    // 다른 경우에도 연결리스트를 수정해도 되지만 연결리스트 수정 작업을 굳이 할 필요 없기때문에
    // 성능을 위해 비슷한 코드임에도 따로 분리.
    if (a[mid_s].count < 3500)
    {
        while (a[max_s].count > 3500 || a[min_s].count > 3500 || a[mid_s].count > 3500)
        {
            if (shead[max_s] == 0)
                break;
            if (stud[shead[max_s]->index] != max_s)
            {
                shead[max_s] = shead[max_s]->next;
            }
            else
            {
                if (a[shead[max_s]->to].count < 3500)
                {
                    // 받는쪽이 3500보다 작을때
                    int temp;
                    if (shead[max_s]->to != mid_s)  // 받는쪽이 아닌것 temp
                    {
                        temp = mid_s;
                    }
                    else
                    {
                        temp = min_s;
                    }
                    struct Node *n1 = shead[max_s]; // 이동하는 학생의 첫번째 노드(연결리스트에 한학생당 노드 2개 존재)
                    struct Node *n2 = 0;    // 연결리스트 수정을 위한 노드
                    struct Node *n3 = 0;    // 이동하는 학생의 2번째 노드
                    int x;
                    int y;
                    // 받는쪽으로 이동
                    a[shead[max_s]->to].count++;    // 받는쪽 학교 학생 수 증가
                    a[max_s].count--;   // 주는쪽 학교 학생 수 감소
                    stud[shead[max_s]->index] = shead[max_s]->to;   // 학교 변경
                    shead[max_s] = shead[max_s]->next;  // 노드 삭제
                    n2 = shead[max_s];
                    while (n2->next != 0)
                    {
                        if (stud[n2->next->index] != max_s) // 이동하는 학생의 두번째 노드 찾음
                        {
                            n3 = n2->next;
                            n2->next = n2->next->next;  // 두번째 노드 제거
                            break;
                        }
                        n2 = n2->next;
                    }
                    if (n3 != 0)    // 두번째 노드를 찾은 경우
                    {
                        // 학생의 학교와의 거리 계산
                        get_student_position(n1->index, &x, &y);
                        int d0 = (a[n1->to].x - x) * (a[n1->to].x - x) + (a[n1->to].y - y) * (a[n1->to].y - y);
                        int d1 = (a[max_s].x - x) * (a[max_s].x - x) + (a[max_s].y - y) * (a[max_s].y - y);
                        int d2 = (a[temp].x - x) * (a[temp].x - x) + (a[temp].y - y) * (a[temp].y - y);
                        // 연결리스트 수정 시 원래 초기 학교로 돌아가는 노드는 필요없음.
                        // 받는쪽에서 나머지로 가는 노드로 만들기
                        n3->d = d2 - d0;
                        n3->to = temp;
                        n3->next = 0;
                        // 받는쪽의 연결리스트에 추가.
                        if (shead[n1->to] == 0)
                        {
                            shead[n1->to] = n3;
                        }
                        else
                        {
                            struct Node *current = shead[n1->to];
                            while ((current->next != 0) && (current->next->d < n3->d))
                            {
                                current = current->next;
                            }
                            n3->next = current->next;
                            current->next = n3;
                        }
                    }
                }
                else if (a[shead[max_s]->to].count == 3500)
                {
                    // 받는쪽이 3500일때
                    // -> 받는쪽에 주고 받는쪽이 나머지에 주는거리합 >= 최대가 다른쪽에 주는 거리 : 최대가 다른쪽에 준다
                    // -> 받는쪽에 주고 받는쪽이 나머지에 주는거리합 < 최대가 다른쪽에 주는 거리 : 최대가 받는쪽에 주고, 받는쪽은 나머지에게 가는 가장 작은거 나머지에 줌
                    int temp;
                    if (shead[max_s]->to == mid_s) // 받는쪽이 학생수 중간인 학교
                    {
                        temp = mid_s;
                    }
                    else // 받는쪽이 학생수 가장적은 학교
                    {
                        temp = min_s;
                    }
                    struct Node *current = shead[max_s]; // 학생 수 최대학교의 헤드
                    struct Node *current_m = &sample;    // 빈노드 사용
                    current_m->next = shead[temp];       // 빈노드 다음은 받는쪽 학교 헤드

                    // 학생 수 최대 학교의 연결리스트에서 나머지에게 주는 가장 적은 경우 찾기.
                    while (current->next != 0)
                    {
                        if (stud[current->next->index] != max_s)
                        {
                            // 이미 다른 학교로 보낸 학생은 제거
                            while (current->next != 0 && stud[current->next->index] != max_s)
                            {
                                current->next = current->next->next;
                            }
                            if (current->next == 0)
                                break;
                        }
                        // 나머지에게 주는 가장 적은 경우
                        if (stud[current->next->index] == max_s && current->next->to != shead[max_s]->to)
                            break;
                        current = current->next;
                    }

                    // 받는 쪽에서 나머지에게 주는 가장 작은 경우 찾기
                    while (current_m->next != 0)
                    {
                        if (stud[current_m->next->index] != temp)
                        {
                            while (current_m->next != 0 && stud[current_m->next->index] != temp)
                            {
                                current_m->next = current_m->next->next;
                            }
                            if (current_m->next == 0)
                                break;
                        }
                        if (stud[current_m->next->index] == temp && current_m->next->to != max_s)
                            break;
                        current_m = current_m->next;
                    }

                    // current->next에는 학생수 최대 학교에서 나머지 학교로 학생을 주는 최소 거리인 경우
                    // current_m->next에는 받는 학교에서 나머지 학교로 학생을 주는 최소 거리인 경우
                    // shead[max_s]에는 현재 최대에서 받는쪽에 주는 최소 거리인 경우
                    // 최대에서 받는쪽 + 받는쪽에서 나머지 < 최대에서 나머지인 경우 : 최대에서 받는쪽으로, 받는쪽에서 나머지로
                    if (current_m->next != 0 && (current->next == 0 || (current->next->d > current_m->next->d + shead[max_s]->d)))
                    {
                        a[shead[max_s]->to].count++;
                        a[current_m->next->to].count++;
                        a[max_s].count--;
                        a[temp].count--;
                        stud[shead[max_s]->index] = shead[max_s]->to;
                        stud[current_m->next->index] = current_m->next->to;
                        // 이동된 노드 제거
                        shead[max_s] = shead[max_s]->next;
                        if (current_m->next == shead[temp])
                        {
                            shead[temp] = shead[temp]->next;
                        }
                        else
                            current_m->next = current_m->next->next;
                    }
                    else // 최대에서 나머지로 준다.
                    {
                        a[current->next->to].count++;
                        a[max_s].count--;
                        stud[current->next->index] = current->next->to;
                        current->next = current->next->next;
                    }
                }
                // 한 학교만 3500초과이고 나머지는 3500미만인 경우 3500 초과에서 3500초과로 학생을 보내는 경우 없음.
            }
        }
    }
    else
    {
        //  학생수 3500 안넘도록 최적화. 3500이 넘는 학교가 없을때까지 반복
        while (a[max_s].count > 3500 || a[min_s].count > 3500 || a[mid_s].count > 3500)
        {
            // 최대, 중간, 최소 다시 맞추기
            if (a[min_s].count > a[mid_s].count)
            {
                int temp = min_s;
                min_s = mid_s;
                mid_s = temp;
            }
            if (a[mid_s].count > a[max_s].count)
            {
                int temp = max_s;
                max_s = mid_s;
                mid_s = temp;
            }
            if (a[min_s].count > a[mid_s].count)
            {
                int temp = min_s;
                min_s = mid_s;
                mid_s = temp;
            }

            // 최대인 학교에서 이동할 학생이 없을 경우 break
            if (shead[max_s] == 0)
                break;

            // 학생수 최대학교의 연결리스트에 있는 학생의 배정학교와 학교가 다른경우->이미 이동한 학생
            if (stud[shead[max_s]->index] != max_s)
            {
                shead[max_s] = shead[max_s]->next; // 연결리스트의 다음으로 이동
            }
            else // 이동할 학생
            {
                if (a[shead[max_s]->to].count < 3500)
                {
                    // 받는쪽이 3500보다 작을때 : 그냥 받음
                    a[shead[max_s]->to].count++;                  // 받는 학교 학생수 증가
                    a[max_s].count--;                             // 주는 학교 학생수 감소
                    stud[shead[max_s]->index] = shead[max_s]->to; // 학생의 배정 학교변경
                    shead[max_s] = shead[max_s]->next;            // 연결리스트에서 제거
                }
                else if (a[shead[max_s]->to].count == 3500)
                {
                    // 받는쪽이 3500일때
                    // -> 받는쪽에 주고 받는쪽이 나머지에 주는거리합 >= 최대가 다른쪽에 주는 거리 : 최대가 다른쪽에 준다
                    // -> 받는쪽에 주고 받는쪽이 나머지에 주는거리합 < 최대가 다른쪽에 주는 거리 : 최대가 받는쪽에 주고, 받는쪽은 나머지에게 가는 가장 작은거 나머지에 줌
                    int temp;
                    if (shead[max_s]->to == mid_s) // 받는쪽이 학생수 중간인 학교
                    {
                        temp = mid_s;
                    }
                    else // 받는쪽이 학생수 가장적은 학교
                    {
                        temp = min_s;
                    }
                    struct Node *current = shead[max_s]; // 학생 수 최대학교의 헤드
                    struct Node *current_m = &sample;    // 빈노드 사용
                    current_m->next = shead[temp];       // 빈노드 다음은 받는쪽 학교 헤드

                    // 학생 수 최대 학교의 연결리스트에서 나머지에게 주는 가장 적은 경우 찾기.
                    while (current->next != 0)
                    {
                        if (stud[current->next->index] != max_s)
                        {
                            // 이미 다른 학교로 보낸 학생은 제거
                            while (current->next != 0 && stud[current->next->index] != max_s)
                            {
                                current->next = current->next->next;
                            }
                            if (current->next == 0)
                                break;
                        }
                        // 나머지에게 주는 가장 적은 경우
                        if (stud[current->next->index] == max_s && current->next->to != shead[max_s]->to)
                            break;
                        current = current->next;
                    }

                    // 받는 쪽에서 나머지에게 주는 가장 작은 경우 찾기
                    while (current_m->next != 0)
                    {
                        if (stud[current_m->next->index] != temp)
                        {
                            while (current_m->next != 0 && stud[current_m->next->index] != temp)
                            {
                                current_m->next = current_m->next->next;
                            }
                            if (current_m->next == 0)
                                break;
                        }
                        if (stud[current_m->next->index] == temp && current_m->next->to != max_s)
                            break;
                        current_m = current_m->next;
                    }

                    // current->next에는 학생수 최대 학교에서 나머지 학교로 학생을 주는 최소 거리인 경우
                    // current_m->next에는 받는 학교에서 나머지 학교로 학생을 주는 최소 거리인 경우
                    // shead[max_s]에는 현재 최대에서 받는쪽에 주는 최소 거리인 경우
                    // 최대에서 받는쪽 + 받는쪽에서 나머지 < 최대에서 나머지인 경우 : 최대에서 받는쪽으로, 받는쪽에서 나머지로
                    if (current_m->next != 0 && (current->next == 0 || (current->next->d > current_m->next->d + shead[max_s]->d)))
                    {
                        a[shead[max_s]->to].count++;
                        a[current_m->next->to].count++;
                        a[max_s].count--;
                        a[temp].count--;
                        stud[shead[max_s]->index] = shead[max_s]->to;
                        stud[current_m->next->index] = current_m->next->to;
                        // 이동된 노드 제거
                        shead[max_s] = shead[max_s]->next;
                        if (current_m->next == shead[temp])
                        {
                            shead[temp] = shead[temp]->next;
                        }
                        else
                            current_m->next = current_m->next->next;
                    }
                    else // 최대에서 나머지로 준다.
                    {
                        a[current->next->to].count++;
                        a[max_s].count--;
                        stud[current->next->index] = current->next->to;
                        current->next = current->next->next;
                    }
                }
                else
                {
                    // 받는쪽이 3500보다 클때
                    // -> max에서 나머지 주는 거리와 받는쪽의 나머지로 주는 거리 비교해 더 작은거로 나머지에 준다.
                    int temp;
                    if (shead[max_s]->to == mid_s)
                    {
                        temp = mid_s; // 받는쪽 = 학생수 중간 학교
                    }
                    else
                    {
                        temp = min_s; // 받는쪽 = 학생수 최소 학교
                    }
                    struct Node *current = shead[max_s]; // 최대 학교 헤드
                    struct Node *current_m = &sample;    // 빈 노드
                    current_m->next = shead[temp];       // 받는 쪽 연결리스트

                    // 최대 학교에서 나머지에 주는 최소 거리 경우 찾기
                    while (current->next != 0)
                    {
                        if (stud[current->next->index] != max_s)
                        {
                            while (current->next != 0 && stud[current->next->index] != max_s)
                            {
                                current->next = current->next->next;
                            }
                            if (current->next == 0)
                                break;
                        }
                        if (stud[current->next->index] == max_s && current->next->to != shead[max_s]->to)
                            break;
                        current = current->next;
                    }
                    // 받는 쪽에서 나머지에 주는 최소 거리 경우 찾기
                    while (current_m->next != 0)
                    {
                        if (stud[current_m->next->index] != temp)
                        {
                            while (current_m->next != 0 && stud[current_m->next->index] != temp)
                            {
                                current_m->next = current_m->next->next;
                            }
                            if (current_m->next == 0)
                                break;
                        }
                        if (stud[current_m->next->index] == temp && current_m->next->to != max_s)
                            break;
                        current_m = current_m->next;
                    }

                    // current->next 는 max에서 나머지에 주는 가장 작은거리 가지는거
                    // current_m->next 는 받는거에서 나머지에 주는 가장 작은거리 가지는거
                    // current->next의 거리 > current_m->next의 거리 : 받는쪽에서 나머지로 학생을 준다.
                    if (current_m->next != 0 && current->next != 0 && current->next->d > current_m->next->d)
                    {
                        a[current_m->next->to].count++;
                        a[temp].count--;
                        stud[current_m->next->index] = current_m->next->to;
                        // 이동한 경우 노드 삭제
                        if (current_m->next == shead[temp])
                        {
                            shead[temp] = shead[temp]->next;
                        }
                        else
                            current_m->next = current_m->next->next;
                    }
                    else if (current_m->next != 0 && current->next != 0) // 최대에서 나머지로 학생을 준다.
                    {
                        a[current->next->to].count++;
                        a[max_s].count--;
                        stud[current->next->index] = current->next->to;
                        // 이동한 경우 노드 삭제
                        current->next = current->next->next;
                    }
                }
            }
        }
    }
    // 학생배열에 있는 배정된 학교로 학생 배정
    for (int i = 0; i < 10000; i++)
    {
        set_student_school(i, stud[i]);
    }
}
