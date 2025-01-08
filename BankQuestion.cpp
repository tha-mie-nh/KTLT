#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h> // Include this header for randomization

// Define the structure for a question
struct Question {
  char content[100]; // Content of the question
  char answerA[50]; // Answer A
  char answerB[50]; // Answer B
  char answerC[50]; // Answer C
  char answerD[50]; // Answer D
  char correctAnswer; // Character representing the correct answer (A, B, C, or D)
};

// Function to add a new question to the question bank
void addQuestion() {
  FILE * txtFile = fopen("nganhangcauhoi.txt", "a");
  if (txtFile == NULL) {
    printf("Khong the mo tep .txt\n");
    return;
  }

  struct Question newQuestion;

  printf("Nhap noi dung cau hoi: ");
  fgets(newQuestion.content, sizeof(newQuestion.content), stdin);
  newQuestion.content[strcspn(newQuestion.content, "\n")] = '\0'; // Remove newline character

  printf("Nhap dap an A: ");
  fgets(newQuestion.answerA, sizeof(newQuestion.answerA), stdin);
  newQuestion.answerA[strcspn(newQuestion.answerA, "\n")] = '\0'; // Remove newline character

  printf("Nhap dap an B: ");
  fgets(newQuestion.answerB, sizeof(newQuestion.answerB), stdin);
  newQuestion.answerB[strcspn(newQuestion.answerB, "\n")] = '\0'; // Remove newline character

  printf("Nhap dap an C: ");
  fgets(newQuestion.answerC, sizeof(newQuestion.answerC), stdin);
  newQuestion.answerC[strcspn(newQuestion.answerC, "\n")] = '\0'; // Remove newline character

  printf("Nhap dap an D: ");
  fgets(newQuestion.answerD, sizeof(newQuestion.answerD), stdin);
  newQuestion.answerD[strcspn(newQuestion.answerD, "\n")] = '\0'; // Remove newline character

  printf("Nhap dap an dung (A, B, C, D): ");
  scanf(" %c", & newQuestion.correctAnswer);
  getchar(); // Consume newline character left by scanf

  // Append new question to the file
  fprintf(txtFile, "%s\n%s\n%s\n%s\n%s\n%c\n", newQuestion.content, newQuestion.answerA, newQuestion.answerB, newQuestion.answerC, newQuestion.answerD, newQuestion.correctAnswer);

  fclose(txtFile);
  printf("Cau hoi da duoc them thanh cong!\n");
}

// Function to take a quiz
void takeQuiz() {
  // Step 1: Read from the .txt file
  FILE * txtFile = fopen("nganhangcauhoi.txt", "r");
  if (txtFile == NULL) {
    printf("Khong the mo tep .txt\n");
    return;
  }

  // Step 2: Convert to appropriate format (e.g., question array)
  struct Question questions[100];
  int numQuestions = 0;

  while (fscanf(txtFile, " %[^\n] ", questions[numQuestions].content) == 1) {
    fscanf(txtFile, " %[^\n] ", questions[numQuestions].answerA);
    fscanf(txtFile, " %[^\n] ", questions[numQuestions].answerB);
    fscanf(txtFile, " %[^\n] ", questions[numQuestions].answerC);
    fscanf(txtFile, " %[^\n] ", questions[numQuestions].answerD);
    fscanf(txtFile, " %c ", & questions[numQuestions].correctAnswer);
    numQuestions++;
  }
  fclose(txtFile);

  // Step 3: Save to .bin file
  FILE * binFile = fopen("nganhangcauhoi.bin", "wb");
  if (binFile == NULL) {
    printf("Khong the mo tep .bin\n");
    return;
  }
  fwrite(questions, sizeof(struct Question), numQuestions, binFile);
  fclose(binFile);

  // Step 4: Read from .bin file
  binFile = fopen("nganhangcauhoi.bin", "rb");
  if (binFile == NULL) {
    printf("Khong the mo tep .bin\n");
    return;
  }
  struct Question readQuestions[100];
  fread(readQuestions, sizeof(struct Question), numQuestions, binFile);
  fclose(binFile);

  // Variable to count correct answers
  int correctAnswers = 0;

  // Step 5: Display questions read from .bin file and prompt user for answers
  for (int i = 0; i < numQuestions; i++) {
    printf("Cau hoi %d: %s\n", i + 1, readQuestions[i].content);
    printf("A. %s\n", readQuestions[i].answerA);
    printf("B. %s\n", readQuestions[i].answerB);
    printf("C. %s\n", readQuestions[i].answerC);
    printf("D. %s\n", readQuestions[i].answerD);
    // Prompt the user to choose an answer
    char userAnswer;
    printf("Chon dap an cua ban (A, B, C, D): ");
    scanf(" %c", & userAnswer);

    // Check the user's answer
    if (userAnswer == readQuestions[i].correctAnswer) {
      correctAnswers++;
    }
  }
  // Step 6: Display the number of correct answers
  printf("Ban da tra loi dung %d/%d cau hoi.\n", correctAnswers, numQuestions);
}
void takeSelectedQuiz(int numQuestions) {
    FILE *txtFile = fopen("nganhangcauhoi.txt", "r");
    if (txtFile == NULL) {
        printf("Khong the mo tep nganhangcauhoi.txt\n");
        return;
    }

    struct Question questions[100];
    int numTotalQuestions = 0;

    // Doc cau hoi tu tep va luu vao mang
    while (fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].content) == 1) {
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerA);
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerB);
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerC);
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerD);
        fscanf(txtFile, " %c ", &questions[numTotalQuestions].correctAnswer);
        numTotalQuestions++;
    }
    fclose(txtFile);

    // Kiem tra xem so luong cau hoi duoc chon co hop le khong
    if (numQuestions <= 0 || numQuestions > numTotalQuestions) {
        printf("So luong cau hoi khong hop le.\n");
        return;
    }

    // Lua chon cau hoi tu mang questions
    printf("Day la %d cau hoi tu tap nganhangcauhoi.txt:\n", numQuestions);
    printf("----------------------------------------------\n");
    int correctAnswers = 0;
    for (int i = 0; i < numQuestions; i++) {
        printf("Cau hoi %d: %s\n", i + 1, questions[i].content);
        printf("A. %s\n", questions[i].answerA);
        printf("B. %s\n", questions[i].answerB);
        printf("C. %s\n", questions[i].answerC);
        printf("D. %s\n", questions[i].answerD);

        // Yeu cau nguoi dung chon dap an
        char userAnswer;
        printf("Chon dap an cua ban (A, B, C, D): ");
        scanf(" %c", &userAnswer);

        // Kiem tra dap an cua nguoi dung
        if (userAnswer == questions[i].correctAnswer) {
            correctAnswers++;
        }
    }
    // Hien thi so cau tra loi dung
    printf("Ban da tra loi dung %d/%d cau hoi.\n", correctAnswers, numQuestions);
}

void takeRandomQuiz(int numQuestions) {
    // Buoc 1: Doc tu tep .txt
    FILE *txtFile = fopen("nganhangcauhoi.txt", "r");
    if (txtFile == NULL) {
        printf("Khong the mo tep nganhangcauhoi.txt\n");
        return;
    }
    // Buoc 2: Chuyen doi sang dinh dang phu hop (vi du: mang cau hoi)
    struct Question questions[100];
    int numTotalQuestions = 0;

    while (fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].content) == 1) {
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerA);
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerB);
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerC);
        fscanf(txtFile, " %[^\n] ", questions[numTotalQuestions].answerD);
        fscanf(txtFile, " %c ", &questions[numTotalQuestions].correctAnswer);
        numTotalQuestions++;
    }
    fclose(txtFile);

    // Buoc 3: Dao vi tri cac cau hoi
    srand(time(NULL)); // Ma cho dao tron
    for (int i = 0; i < numTotalQuestions - 1; i++) {
        int j = i + rand() / (RAND_MAX / (numTotalQuestions - i) + 1);
        struct Question temp = questions[j];
        questions[j] = questions[i];
        questions[i] = temp;
    }

    // Buoc 4: Chon N cau hoi dau tien
    struct Question selectedQuestions[100];
    for (int i = 0; i < numQuestions; i++) {
        selectedQuestions[i] = questions[i];
    }

    // Buoc 5: Hien thi va yeu cau nguoi dung chon dap an
    printf("Day la %d cau hoi ngau nhien tu tap nganhangcauhoi.txt:\n", numQuestions);
    printf("----------------------------------------------\n");
    int correctAnswers = 0;
    for (int i = 0; i < numQuestions; i++) {
        printf("Cau hoi %d: %s\n", i + 1, selectedQuestions[i].content);
        printf("A. %s\n", selectedQuestions[i].answerA);
        printf("B. %s\n", selectedQuestions[i].answerB);
        printf("C. %s\n", selectedQuestions[i].answerC);
        printf("D. %s\n", selectedQuestions[i].answerD);

        // Yeu cau nguoi dung chon dap an
        char userAnswer;
        printf("Chon dap an cua ban (A, B, C, D): ");
        scanf(" %c", &userAnswer);

        // Kiem tra dap an cua nguoi dung
        if (userAnswer == selectedQuestions[i].correctAnswer) {
            correctAnswers++;
        }
    }
    // Buoc 6: Hien thi so cau tra loi dung
    printf("Ban da tra loi dung %d/%d cau hoi.\n", correctAnswers, numQuestions);
}

int main() {
  int choice;
  while (1) {
    printf("Chon chuc nang:\n");
    printf("1. Them cau hoi moi\n");
    printf("2. Lam bai kiem tra\n");
    printf("3. Lam bai kiem tra tu so luong cau hoi duoc chon\n");
    printf("4. Lam bai kiem tra voi so luong cau hoi ngau nhien\n");
    printf("5. Thoat\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", & choice);
    getchar(); // Consume newline character left by scanf

    switch (choice) {
    case 1:
      addQuestion();
      break;
    case 2:
      takeQuiz();
      break;
    case 3: {
      int numQuestions;
      printf("Nhap so luong cau hoi ban muon lam: ");
      scanf("%d", & numQuestions);
      getchar(); // Consume newline character left by scanf
      takeSelectedQuiz(numQuestions);
      break;
    }
    case 4: {
      int numQuestions;
      printf("Nhap so luong cau hoi ban muon lam: ");
      scanf("%d", & numQuestions);
      getchar(); // Consume newline character left by scanf
      takeRandomQuiz(numQuestions);
      break;
    }
    case 5:
      printf("Thoat chuong trinh.\n");
      return 0;
    default:
      printf("Lua chon khong hop le. Vui long thu lai.\n");
    }
  }
  return 0;
}

