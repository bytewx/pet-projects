import React, { useState, useEffect } from 'react'
import './App.css'
import TodoList from './components/TodoList.tsx';
import axios from 'axios'

interface Task {
  _id: string;
  title: string;
  completed: boolean;
}

const App: React.FC = () => {
  const [tasks, setTasks] = useState<Task[]>([]);
  const [task, setTask] = useState<string>("");
  const [editingTaskID, setEditingTaskID] = useState<string | null>(null);
  const [editingTitle, setEditingTitle] = useState<string>("");

  useEffect(() => {
    const fetchTasks = async () => {
      try {
        const response = await axios.get<Task[]>('http://localhost:5000/api/tasks');
        console.log("Fetched tasks: ", response.data);
        setTasks(response.data);
      } catch (error) {
        console.error("Error fetching tasks: ", error);
      }
    };

    fetchTasks();
  }, []);

  const addTask = async () => {
    if (!task) return;

    try {
      console.log("Adding task: ", task);
      const response = await axios.post<Task>(
        'http://localhost:5000/api/tasks', 
        { title: task }, 
        { headers: { "Content-Type": "application/json" } }
      );

      console.log("Task added response: ", response.data);
      setTasks([...tasks, response.data]);
      setTask("");
    } catch (error) {
      console.error("Error adding task: ", error);
    }
  }

  const deleteTask = async (id: string) => {
    try {
      await axios.delete(`http://localhost:5000/api/tasks/${id}`);
      setTasks(tasks.filter((task) => task._id !== id));
    } catch (error) {
      console.error("Error deleting task: ", error);
    }
  }

  const updateTask = async (id: string, updatedTask: Partial<Task>) => {
    try {
      const response = await axios.put<Task>(
        `http://localhost:5000/api/tasks/${id}`,
        updatedTask,
        { headers: { "Content-Type": "application/json" } }
      );

      setTasks(
        tasks.map((task) => 
          task._id === id ? { ...task, ...response.data } : task
        )
      );

      setEditingTaskID(null);
      setEditingTitle("");
    } catch (error) {
      console.error("Error deleting task: ", error);
    }
  }

  const startEditing = (id: string) => {
    setEditingTaskID(id);
  };

  const handleEditChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setEditingTitle(e.target.value);
  }

  return (
    <div className="App">
      <h1>Todo App</h1>
      <div>
        <input 
          type="text"
          value={task}
          onChange={(e) => setTask(e.target.value)} 
        />
        
        <button onClick={addTask}>Add Task</button>
      </div>
      <TodoList 
        tasks={tasks}
        deleteTask={deleteTask}
        updateTask={updateTask}
        editingTitle={editingTitle}
        setEditingTitle={setEditingTitle}
        editingTaskID={editingTaskID}
        setEditingTaskID={setEditingTaskID}
        startEditing={startEditing}
        handleEditChange={handleEditChange}
      />
    </div>
  );
};

export default App;