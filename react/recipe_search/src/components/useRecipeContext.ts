import { useContext } from 'react';
import { RecipeContext } from './RecipeProvider';

export const useRecipeContext = () => {
  const context = useContext(RecipeContext);

  if (context === null) {
    throw new Error("useTextContext must be used within a TextProvider");
  }
    return context;
};