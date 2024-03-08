import React, { useState } from "react";
import "../styles.css";
import { Todo, TodosList } from "../interfaces";
import FilterDone from "./Filter";
import Todos from "./Todos";

export function AddTodo({ todoThings, setTodoThings }: TodosList) {
  const [newTask, setNewTask] = useState<string>("");

  const addTodo = () => {
    if (newTask.trim() !== "") {
      const newTodo: Todo = { task: newTask, done: false };
      setTodoThings([...todoThings, newTodo]);
      setNewTask("");
    }
  };

  return (
    <main>
      <div className="todo-container">
        <Todos todoThings={todoThings} setTodoThings={setTodoThings} />
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
      <FilterDone todoThings={todoThings} setTodoThings={setTodoThings} />
    </main>
  );
}
