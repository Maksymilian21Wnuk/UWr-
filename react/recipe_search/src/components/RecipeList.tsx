import { useRecipeContext } from './useRecipeContext';
import { useState } from 'react';


// displays recipe list, also implements removal adding to fav
export const RecipeList = () => {
    const { state, dispatch } = useRecipeContext();
    const [filtered, setFilter] = useState('');
    const [show_favorite, setShowFavorite] = useState(false);

    // fiter by state from context used by input
    const filteredRecipes = state.recipes.filter(recipe =>
      (recipe.name.toLowerCase().includes(filtered.toLowerCase()) ||
      recipe.recipe_text.toLowerCase().includes(filtered.toLowerCase())) &&
      (show_favorite ? recipe.isFavorite : true)
  );

    // dispatch to remove a recipe
    const removeRecipe = (id : string) => {
        dispatch({ type: 'REMOVE_RECIPE', payload: id });
    };
    // dispatch to add favorite
    const addToFavorite = (id : string) => {
      dispatch({type : 'TOGGLE_FAVORITE', payload: id});
    }

    return (
        <div>
            <h2 className='recipe-header'>Recipes</h2>
            <div className='button-container'>
            <input
                type="text"
                placeholder="Search Recipes"
                value={filtered}
                onChange={(e) => setFilter(e.target.value)}
            />
              <button className="fav_button" onClick={() => setShowFavorite(!show_favorite)}>
                {show_favorite ? 'Show all' : 'Show favorites'}
              </button>
            </div>
            <ul className="recipe-list">
                {filteredRecipes.map(recipe => (
                    <li key={recipe.id} className="recipe-item">
                        <div className="recipe-box">
                            <h3 className="recipe-name">{recipe.name}</h3>
                            <p><strong>Recipe:</strong> {recipe.recipe_text}</p>
                            <button onClick={() => removeRecipe(recipe.id)}>Remove</button>
                            <button onClick={() => addToFavorite(recipe.id)}>
                              {recipe.isFavorite ? "Remove from Favorite" : "Favorite"}
                            </button>
                        </div>
                    </li>
                ))}
            </ul>
        </div>
    );
};