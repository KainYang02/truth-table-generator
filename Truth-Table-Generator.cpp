#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

void wrong_equation() {
  printf("The Equation is not standard.\nTry again!\n");
  exit(0);
}

void print_equation(string S) {
  int n = S.size();
  for (int i = 0; i < n; i++) {
    if (S[i] == 0) putchar('F');
    else if (S[i] == 1) putchar('T');
    else putchar(S[i]); 
  }
  puts("");
}

char cl[9] = {' ', '&', '|', '!', '-', '<', '>', '(', ')'};
bool ap[26], vl[26];
int match[510];
vector<vector<char>> ans;
string S;

bool cmp(const pi a, const pi b) {
  return a.second - a.first < b.second - b.first;
}

void init() {
  int n = S.size();
  // �Ƿ��ַ� 
  for (int i = 0; i < n; i++) {
    if ('a' <= S[i] && S[i] <= 'z') S[i] -= 32; 
    bool tmp = 0;
    if ('A' <= S[i] && S[i] <= 'Z') tmp = 1, ap[S[i] - 'A'] = 1;
    for (int j = 0; j < 9; j++) if (S[i] == cl[j]) tmp = 1;
    if (!tmp) wrong_equation();
  }
  // ����ǺŻ�
  string SS = "";
  for (int i = 0; i < n; i++) {
    if ('A' <= S[i] && S[i] <= 'Z') SS = SS + S[i];
    if (S[i] == '(' || S[i] == ')') SS = SS + S[i];
    if (S[i] == '!') SS = SS + '1';
    if (S[i] == '&') SS = SS + '2';
    if (S[i] == '|') SS = SS + '3';
    if (S[i] == '-') {
      if (S[i - 1] == '>') wrong_equation();
      if (S[i + 1] == '<') wrong_equation();
      bool l = S[i - 1] == '<', r = S[i + 1] == '>';
      if (!l && !r) wrong_equation();
      else if (!l) SS = SS + '4';
      else if (!r) SS = SS + '5';
      else SS = SS + '6';
    }
  } 
  S = SS, n = S.size();
  
//cout << S << endl;
  
  // ����������
  stack<int> st;
  for (int i = 0; i < n; i++) {
    if (S[i] == '(') st.push(i);
    if (S[i] == ')') {
      if (!st.size()) wrong_equation();
      int u = st.top(), v = i;
      match[u] = v;
      match[v] = u;
      st.pop();
    }
  } 
  if (st.size()) wrong_equation();
  
//for (int i = 0; i < 26; i++) if (ap[i]) cout << (char)(i + 'A') << " ";
//cout << endl;
//for (int i = 0; i < n; i++) if (match[i]) cout << i << " " << match[i] << endl;

}

bool ck_in(char c, char l, char r) {
  return l <= c && c <= r;
}

int calc(string S) {
  string S_ = ""; int n = S.size();
  for (int i = 0; i < n; i++) { // !
    if (S[i] == '1') {
      if (i + 1 == n || ck_in(S[i + 1], '1', '6')) wrong_equation();
      S_ += !S[i + 1];
      i += 1;
    } else {
      S_ += S[i];
    }
  }
  S = S_, n = S.size(), S_ = "";
  for (int i = 0; i < n; i++) { // &
    if (i < n && S[i + 1] == '2') {
      if (i + 1 == n - 1 || ck_in(S[i], '1', '6') || ck_in(S[i + 2], '1', '6')) wrong_equation();
      S_ += (char) ((int) S[i] & (int) S[i + 2]); 
      i += 2;
    } else {
      S_ += S[i];
    } 
  } 
  S = S_, n = S.size(), S_ = "";
  for (int i = 0; i < n; i++) { // |
    if (i < n && S[i + 1] == '3') {
      if (i + 1 == n - 1 || ck_in(S[i], '1', '6') || ck_in(S[i + 2], '1', '6')) wrong_equation();
      S_ += (char) (S[i] | S[i + 2]); 
      i += 2;
    } else {
      S_ += S[i];
    }
  }
  S = S_, n = S.size(), S_ = "";
  for (int i = 0; i < n; i++) { // ->
    if (i < n && S[i + 1] == '4') {
      if (i + 1 == n - 1 || ck_in(S[i], '1', '6') || ck_in(S[i + 2], '1', '6')) wrong_equation();
      S_ += (char) ((!S[i]) | S[i + 2]); 
      i += 2;
    } else {
      S_ += S[i];
    }
  }
  S = S_, n = S.size(), S_ = "";
  for (int i = 0; i < n; i++) { // <-
    if (i < n && S[i + 1] == '5') {
      if (i + 1 == n - 1 || ck_in(S[i], '1', '6') || ck_in(S[i + 2], '1', '6')) wrong_equation();
      S_ += (char) (S[i] | (!S[i + 2])); 
      i += 2;
    } else {
      S_ += S[i];
    }
  }
  S = S_, n = S.size(), S_ = "";
  for (int i = 0; i < n; i++) { // <->
    if (i < n && S[i + 1] == '6') {
      if (i + 1 == n - 1 || ck_in(S[i], '1', '6') || ck_in(S[i + 2], '1', '6')) wrong_equation();
      S_ += (char) (S[i] == S[i + 2]); 
      i += 2;
    } else {
      S_ += S[i];
    }
  }
  S = S_, n = S.size(), S_ = "";
  if (n != 1) wrong_equation();
//  cout << (int)S[0] << endl;
  return S[0];
}

int solve(string SS, int l, int r) {
  string S_new = "";
  for (int i = l + 1; i < r; i++) {
    if (SS[i] == '(') {
      S_new += (char) solve(SS, i, match[i]);
      i = match[i];
    } else {
      S_new += SS[i];
    }
  }
  return calc(S_new);
}

void dfs(int stp) {
  if (stp == 26) { 
    string SS = S; int n = S.size();
    for (int i = 0; i < n; i++) {
      if ('A' <= S[i] && S[i] <= 'Z') {
        SS[i] = vl[S[i] - 'A'] ? 1 : 0;
      }
    }
    vector<char> cur;
    for (int i = 0; i < 26; i++) if (ap[i]) cur.push_back(vl[i] + '0');
    cur.push_back(solve(SS, 0, n - 1) + '0');
    ans.push_back(cur);
    return;
  }
  dfs(stp + 1);
  if (ap[stp]) {
    vl[stp] = 1;
    dfs(stp + 1);
    vl[stp] = 0;
  }
}

// (A->B)&((A&C)<->(!C<-B)) 

int main() {
  printf(
    "Truth Table Generator\n"
    "powered by ����\n\n"
    "ʹ��ָ��:\n"
    "!!!������ʹ��Ӣ�ı��!!!\n" 
    "�� : &\n"
    "�� : |\n"
    "�� : !\n"
    "�̺� : -> �� <-\n" 
    "˫�̺� : <->\n"
    "���ȼ� ��() > �� > & > | > -> > <->\n" 
    "���� : ��ĸ �����ִ�Сд (��a��A��ͬһ������,�����������ֵ���ʱ���ͳһΪA)\n\n"
    "�벻Ҫ������һ��->��<-�����ȼ�����Ϊ�������û�ж��壬�������Ҳ�㲻����\n"
    "����: A<-B->C���������Ź涨����˳��A<-(B->C)��(A<-B)->C\n\n"
  );
//  S = "(A->B)&((A&C)<->(!C<-B))";
  cin >> S;
  S = " (" + S + ") "; // ���㴦�� 
  init();
  vector<char> cur;
  for (int i = 0; i < 26; i++) if (ap[i]) cur.push_back(i + 'A');
  if (!cur.size()) wrong_equation();
  cur.push_back('*');
  ans.push_back(cur); 
  dfs(0);
  for (auto tmp : ans) {
    for (auto c : tmp) {
      cout << c << " ";
    }
    cout << endl;
  }
  return 0;
} 
