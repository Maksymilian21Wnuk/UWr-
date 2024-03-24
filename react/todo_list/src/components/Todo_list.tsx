import React, { useState } from "react";
import "../styles.css";
import { Todo, TodosList } from "../interfaces";
import Todos from "./Todos";

export function AddTodo({ todoThings, setTodoThings }: TodosList) {
  const [newTask, setNewTask] = useState<string>("");
  const [checked, setChecked] = useState(false);

  const addTodo = () => {
    if (newTask.trim() !== "") {
      const newTodo: Todo = { task: newTask, done: false };
      setTodoThings([...todoThings, newTodo]);
      setNewTask("");
    }
  };

  const applyChecked = () => {
    if (!checked) {
      setChecked(true);
    } else {
      setChecked(false);
    }
  };

  return (
    <main>
      <div className="todo-container">
        <Todos
          todoThings={todoThings}
          setTodoThings={setTodoThings}
          checked={checked}
        />
        <form
          onSubmit={(e) => {
            e.preventDefault();
          }}
        >
          <input
            type="text"
            value={newTask}
            onChange={(e) => setNewTask(e.target.value)}
            placeholder="Add new todo"
          />
          <button onClick={addTodo} type="submit">
            Add
          </button>
        </form>
      </div>
      <div className="filter_done">
        <button onClick={applyChecked}>Show only checked todos</button>
      </div>
    </main>
  );
}
