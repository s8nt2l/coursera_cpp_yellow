#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <map>
#include <set>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void operator+=(TasksInfo& a, TasksInfo& b){
    a[TaskStatus::NEW] += b[TaskStatus::NEW];
    a[TaskStatus::IN_PROGRESS] += b[TaskStatus::IN_PROGRESS];
    a[TaskStatus::TESTING] += b[TaskStatus::TESTING];
    a[TaskStatus::DONE] += b[TaskStatus::DONE];
}

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return db.at(person);
    }
    
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person){
        db[person][TaskStatus::NEW]++;
    }
    
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count){//2 3 
        /*TasksInfo sourse;
        sourse[TaskStatus::NEW] = 0;
        int r = task_count;

        pair a = IsLow(db[person][TaskStatus::NEW] - task_count);
        db[person][TaskStatus::NEW] = a.first;
        r = a.second;
        sourse[TaskStatus::IN_PROGRESS] = r;
        db[person][TaskStatus::IN_PROGRESS] += task_count - r;

        a = IsLow(db[person][TaskStatus::IN_PROGRESS] - r);
        db[person][TaskStatus::IN_PROGRESS] = a.first;*/
        TasksInfo updated, untoched;
        int r = task_count;
        r -= db[person][TaskStatus::NEW];
        if(r < 0){
            updated[TaskStatus::NEW] = -r;
            updated[TaskStatus::IN_PROGRESS] = task_count; 
            untoched = db[person];
            db[person] += updated;
            return tie(updated, untoched);
        }
        updated[TaskStatus::IN_PROGRESS] += db[person][TaskStatus::NEW];
        updated[TaskStatus::NEW] = 0;
        r -= db[person][TaskStatus::IN_PROGRESS];
        if(r < 0){
            //db[person][TaskStatus::IN_PROGRESS] += -r;
            updated[TaskStatus::TESTING] = -r; 
            auto t = tie(updated, untoched);
            untoched = db[person];
            db[person] += updated;
            return ;
        }
        db[person][TaskStatus::TESTING] += -r;
        db[person][TaskStatus::IN_PROGRESS]

    }
private:
    pair<int, int> IsLow(const int& a){
        return (a < 0) ? make_pair(0, abs(a)) : make_pair(a, 0);
    }
    map<string, TasksInfo> db;
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
    ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
    ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
    ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    
    TasksInfo updated_tasks, untouched_tasks;
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    system("pause");
    return 0;
}