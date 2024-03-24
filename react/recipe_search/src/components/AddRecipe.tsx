import React, { useState } from 'react';
import { useRecipeContext } from './useRecipeContext';


// adds recipe using form
export const AddRecipeForm = () => {
    const { dispatch } = useRecipeContext();
    const [name, setName] = useState('');
    const [recipe_text, setIngredients] = useState('');
  
    const handleSubmit = (e: React.FormEvent) => {
      e.preventDefault();
      const newRecipe = {
        id: name, // Assuming names are not same ( i know its wrong )
        name,
        recipe_text,
        isFavorite: false // Assuming not fav bty default
      };
      dispatch({ type: 'ADD_RECIPE', payload: newRecipe });
    };
  
    return (
      <form onSubmit={handleSubmit} className='form'>
        <input
          type="text"
          placeholder="Recipe Name"
          value={name}
          onChange={(e) => setName(e.target.value)}
        />
        <input
          type="text"
          placeholder="Recipe"
          value={recipe_text}
          onChange={(e) => setIngredients(e.target.value)}
        />
        <button type="submit">Add Recipe</button>
      </form>
    );
  };