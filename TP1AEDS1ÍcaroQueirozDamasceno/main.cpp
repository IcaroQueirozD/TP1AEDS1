#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "list.hpp"
#include "functions.cpp"

using namespace std;

bool ReadFile(EmpList *list)
{
  ifstream file;
  file.open("Employees.bin", fstream::binary);

  if (file.fail())
  {
    file.clear();
    return false;
  }

  bool isFirstLine = true;

  while (file.peek() != ifstream::traits_type::eof())
  {
    if (isFirstLine)
    {
      unsigned int id;
      file >> id;
      isFirstLine = false;
    }
    else
    {
      ItemType *employee = new ItemType();
      file.read((char *)employee, sizeof(ItemType));

      InsertLast(list, employee);
    }
  }

  file.clear();
  return true;
}

bool SaveFile(EmpList *list)
{
  ofstream file;
  file.open("Employees.bin", ofstream::trunc | fstream::binary);

  if (file.fail())
  {
    file.clear();
    return false;
  }

  Pointer aux = list->First->next;
  while (aux != NULL)
  {
    ItemType employee = aux->item;
    file.write((char *)&employee, sizeof(ItemType));

    Pointer prev = aux;
    aux = aux->next;
    delete prev;
  }
  return true;
}

void menu()
{
  system("cls");
  cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n";
  cout << "▓                           ▓\n";
  cout << "▓   PERSONNEL DEPARTMENT    ▓\n";
  cout << "▓                           ▓\n";
  cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n";
  cout << "\n1. Add new employee\n";
  cout << "2. Add new projects\n";
  cout << "3. Delete projects\n";
  cout << "4. Delete employees not working on projects\n";
  cout << "5. Find employee\n";
  cout << "6. Print payslip\n";
  cout << "0. Exit\n";
}

int main()
{
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);

  EmpList employeeL; //Declaração da lista encadeada.
  ItemType item;
  projList projL; //Declaração da lista sequencial.
  Pointer p;
  int choice, idchoice, iddeletion;
  char yn1, yn2;
  float baseSalary, salary, INSS, IncomeTax;

  ItemType employee;
  ProjType project;

  CreateEmptyList(&employeeL);

  ReadFile(&employeeL);

  do
  {

    menu();
    cout << "\n\n";
    cin >> choice;
    cin.ignore();
    switch (choice) //Escolha das opções do menu.
    {
    case 1:
    {

      system("cls");
      cout << "Type the employee information:\n\n"; //Inserção das informações do funcionário.
      cout << "Employee ID: ";
      cin >> employee.id;
      cin.ignore();
      cout << "Employee name: ";
      cin.getline(employee.name, 30);
      cout << "\nEmployee address:\n"
           << "State: ";
      cin.getline(employee.adrss.state, 30);
      cout << "City: ";
      cin.getline(employee.adrss.city, 30);
      cout << "Borough: ";
      cin.getline(employee.adrss.borough, 30);
      cout << "Street name: ";
      cin.getline(employee.adrss.street, 30);
      cout << "House number: ";
      cin >> employee.adrss.housenum;
      cout << "Number of dependents: ";
      cin >> employee.dependents;

      projCreateEmptyList(&employee.projects); //Após inserir as informações do funcionário, a lista sequencial é criada.

      InsertLast(&employeeL, &employee); //Inserção das informações do funcionário na lista encadeada.
      do
      {
        cout << "Do you wish to add projects to this employee? (Y/N)\n\n"; //O programa pergunta se o usuário já quer inserir um projeto.
        cin >> yn1;
      } while (yn1 != 'Y' && yn1 != 'N');

      if (yn1 == 'Y')
      {
        do
        {
          system("cls");
          cout << "Project insertion:\n\n"; //Inserção de informações do projeto no programa.
          cout << "Project ID: ";
          cin >> project.projid;
          cin.ignore();
          cout << "Project Name: ";
          cin.getline(project.projname, 30);
          cout << "Number of weekly work hours: ";
          cin >> project.projhours;
          p = FindItem(&employeeL, employee.id);
          projInsertItem(&p->item.projects, project); //Inserção de informações do projeto na lista sequencial.
          cout << "\n\nDo you wish to add more projects? (Y/N)\nAvailable number of projects: " << endl;
          cin >> yn2;
          if (yn2 != 'Y') //Se a resposta for diferente de "sim", o programa retorna ao menu principal.
          {
            break;
          }

        } while (yn2 == 'Y');
      }

      cout << "Employee succesfully added.";
    }

    break;
    case 2:
      system("cls");
      cout << "Input the ID of the employee you wish to add projects to: ";
      cin >> idchoice;
      PrintItem(&employeeL, idchoice);
      cout << "\n\nProject insertion:\n\n"; // Ao encontrar o funcionário, o usuário deve então inserir as informações do projeto.
      cout << "Project ID: ";
      cin >> project.projid;
      cin.ignore();
      cout << "Project Name: ";
      cin.getline(project.projname, 30);
      cout << "Number of weekly work hours: ";
      cin >> project.projhours;
      p = FindItem(&employeeL, idchoice);
      if (p == NULL) // Se o funcionário não for encontrado, o usuário deve inserir as informações novamente.
      {
        do
        {
          cout << "Error, ID not found, please try again.\n";
          system("pause");
          system("cls");
          cout << "Input the ID of the employee you wish to add projects to: ";
          cin >> idchoice;
          p = FindItem(&employeeL, idchoice);
          projInsertItem(&p->item.projects, project);
        } while (p == NULL);
      }
      else
      {
        projInsertItem(&p->item.projects, project);
        cout << "Project succesfully added.";
      }

      break;
    case 3:
      system("cls");
      cout << "Input the ID of the employee whose project you wish to delete: ";
      cin >> idchoice;
      PrintItem(&employeeL, idchoice);
      cout << "\n\nProject deletion:\n\n";
      projPrintList(p->item.projects);
      p = FindItem(&employeeL, idchoice);
      cout << "Input the ID of the project you want to delete: "; // Ao encontrar o funcionário, a função remove o projeto com o ID inserido.
      cin >> iddeletion;
      projRemoveItem(&p->item.projects, iddeletion);
      cout << "Project succesfully deleted!";
      break;
    case 4:
      system("cls");
      p = employeeL.First->next;
      while (p != NULL) // Enquanto p for diferente de NULL, o funcionário é removido se sua lista sequencial tiver um tamanho = 0.
      {
        if (p->item.projects.projSize == 0)
        {
          RemoveItemById(&employeeL, p->item.id);
        }
        p = p->next;
      }
      cout << "The employees not working on any projects have been deleted.";
      system("pause");
      break;
    case 5:
      system("cls");
      cout << "Input the ID of the employee you want to find: ";
      cin >> idchoice;
      p = FindItem(&employeeL, idchoice);
      if (p == NULL) // Se p receber um valor nulo, então o funcionário não foi encontrado.
      {
        cerr << "Error, ID not found, please try again.\n";
        system("pause");
        system("cls");
        do
        {
          cout << "Input the ID of the employee you want to find: ";
          cin >> idchoice;
          p = FindItem(&employeeL, idchoice);
          PrintItem(&employeeL, idchoice);
          projPrintList(p->item.projects);
        } while (p == NULL);
      }
      else
      {
        PrintItem(&employeeL, idchoice);
        projPrintList(p->item.projects);
        system("pause");
      }

      break;
    case 6:
      system("cls");
      p = employeeL.First->next;
      while (p != NULL) // Enquanto p não apontar pra NULL, ou seja, até o término da lista.
      {
        int salCount = 0;
        for (int i = 0; i < p->item.projects.projSize; i++)
        {
          salCount += p->item.projects.projItem[i].projhours;
        }

        baseSalary = salCount * 45 + p->item.dependents * 35; // Cálculo do salário bruto.
        INSS = baseSalary * 0.085;                            // Cálculo do disconto do INSS.
        IncomeTax = baseSalary * 0.15;                        // Cálculo do imposto de renda.
        salary = baseSalary - INSS - IncomeTax;               // Cálculo do salário líquido.

        cout << "Employee ID: " << p->item.id << endl;
        cout << "Name: " << p->item.name << endl;
        cout << "Number of dependents: " << p->item.dependents << endl;
        cout << "Number of hours working on a project: " << salCount << "\n\n";
        cout << "Base salary:\t"
             << baseSalary << endl;
        cout << "Income tax discounted: " << IncomeTax << endl;
        cout << "INSS discount: " << INSS << endl;
        cout << "Final salary: " << salary << "\n\n";
        p = p->next;
      }
      system("pause");
      break;
    }

  } while (choice != 0);

  SaveFile(&employeeL);    // Salva a lista em um arquivo binário.
  RemoveFirst(&employeeL); // Deleta e desaloca a memória da lista.

  cout << endl;
  return 0;
}