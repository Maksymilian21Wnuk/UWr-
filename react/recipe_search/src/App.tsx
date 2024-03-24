import './App.css'
import {AddRecipeForm} from './components/AddRecipe'
import { RecipeList } from './components/RecipeList'
import { RecipeProvider } from './components/RecipeProvider'

function App() {

  return (
    <RecipeProvider>
      <h1>Recipes of your favourite meals!</h1>
      <AddRecipeForm/>
      <RecipeList/>
    </RecipeProvider>
  )
}

export default App
