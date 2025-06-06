import React from 'react';

interface Task {
    _id: string;
    title: string;
    completed: boolean;
}

interface TodoListProps {
    tasks: Task[];
    deleteTask: (id: string) => void;
    updateTask: (id: string, updatedTask: Partial<Task>) => void;
    editingTitle: string;
    setEditingTitle: (title: string) => void;
    editingTaskID: string | null;
    setEditingTaskID: (id: string | null) => void;
    startEditing: (id: string, title: string) => void;
    handleEditChange: (e: React.ChangeEvent<HTMLInputElement>) => void;
}

const TodoList: React.FC<TodoListProps> = ({
    tasks,
    deleteTask,
    updateTask,
    editingTitle,
    setEditingTitle,
    editingTaskID,
    setEditingTaskID,
    startEditing,
    handleEditChange,
}) => {
    return (
        <ul>
            {tasks.map((task) => (
                <li key={task._id}>
                    <input 
                        type="checkbox"
                        checked={task.completed}
                        onChange={() => updateTask(task._id, { completed: !task.completed })} 
                    />
                    {editingTaskID === task._id ? (
                        <>
                            <input type="text" value={editingTitle} onChange={handleEditChange} />
                            <button
                                onClick={() => {
                                    updateTask(task._id, { title: editingTitle });
                                    setEditingTaskID(null);
                                }}
                            >
                                Save
                            </button>
                        </>
                    ) : (
                        <>
                            <span style={{ textDecoration: task.completed ? 'line-through' : 'none' }}>
                                {task.title}
                            </span>

                            <div>
                                <button onClick={() => deleteTask(task._id)}>Delete</button>
                                <button
                                    onClick={() => {
                                        startEditing(task._id, task.title);
                                        setEditingTitle(task.title);
                                    }}
                                >
                                    Edit
                                </button>
                            </div>
                        </>
                    )};
                </li>
            ))};
        </ul>
    );
};

export default TodoList;