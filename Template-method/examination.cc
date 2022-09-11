/*
** All students with same problems in the same examination, how to have a class
** that generates examinations?
*/

#include <iostream>
#include <string>
using namespace std;

class Exam {
public:
  virtual void DoProb1() { cout << "Prob 1, a: a, b:b, c:c, d:d " << endl; }
  virtual void DoProb2() { cout << "Prob 2, a: a, b:b, c:c, d:d " << endl; }
  virtual void DoProb3() { cout << "Prob 3, a: a, b:b, c:c, d:d " << endl; }
};

class ExamA : public Exam {
public:
  void DoProb1() override {
    Exam::DoProb1();
    cout << "Student A prob1 answer: a" << endl;
  }

  void DoProb2() override {
    Exam::DoProb2();
    cout << "Student A prob2 answer: b" << endl;
  }

  void DoProb3() override {
    Exam::DoProb3();
    cout << "Student A prob3 answer: c" << endl;
  }
};

class ExamB : public Exam {
public:
  void DoProb1() override {
    Exam::DoProb1();
    cout << "Student B prob1 answer: c" << endl;
  }

  void DoProb2() override {
    Exam::DoProb2();
    cout << "Student B prob2 answer: b" << endl;
  }

  void DoProb3() override {
    Exam::DoProb3();
    cout << "Student B prob3 answer: a" << endl;
  }
};

int main(int argc, char *argv[]) {

  // Exam for student a.
  auto *exam_a = new ExamA();
  exam_a->DoProb1();
  exam_a->DoProb2();
  exam_a->DoProb3();

  // Exam for student b.
  auto *exam_b = new ExamB();
  exam_b->DoProb1();
  exam_b->DoProb2();
  exam_b->DoProb3();

  return 0;
}

/*
** There are many code duplications. The flow of answer a problem as follows:
** - Shows the problem.
** - Answers the problem.
**
** For every student, every answering procedure is same, and the difference
** exists only in specific sub procedures (answer problem). For a set of
** behavior that are identical as a whole and tiny differences in sub behavior,
** it's suitable to use template pattern to simplify code.
*/

class TemplateExam {
public:
  // Extracts the common behavior as listing problem and answering problem.
  // The answering part is declared as virtual for child class to have different
  // behavior.
  void DoProb1() {
    cout << "Prob 1, a: a, b:b, c:c, d:d " << endl;
    cout << "Prob1 answer: " << AnsProb1() << endl;
  }

  void DoProb2() {
    cout << "Prob 2, a: a, b:b, c:c, d:d " << endl;
    cout << "Prob2 answer: " << AnsProb2() << endl;
  }

  void DoProb3() {
    cout << "Prob 3, a: a, b:b, c:c, d:d " << endl;
    cout << "Prob3 answer: " << AnsProb3() << endl;
  }

  // This is the procedure children may be different.
  virtual std::string AnsProb1() { return ""; }
  virtual std::string AnsProb2() { return ""; }
  virtual std::string AnsProb3() { return ""; }
};

class TemplateExamA : public TemplateExam {
public:
  std::string AnsProb1() override { return "a"; }
  std::string AnsProb2() override { return "b"; }
  std::string AnsProb3() override { return "c"; }
};

class TemplateExamB : public TemplateExam {
public:
  std::string AnsProb1() override { return "c"; }
  std::string AnsProb2() override { return "b"; }
  std::string AnsProb3() override { return "a"; }
};
