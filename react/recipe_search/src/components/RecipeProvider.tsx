import { createContext, useReducer } from "react";

type State = {
    recipes: Recipe[];
};

// action types for reducer
type Action = 
    | { type: 'ADD_RECIPE'; payload: Recipe }
    | { type: 'REMOVE_RECIPE'; payload: string }
    | { type: 'TOGGLE_FAVORITE'; payload: string };

    
type Recipe = {
    id: string;
    name: string;
    recipe_text: string;
    isFavorite: boolean;
};

// some initial recipes
const initialState = {
    recipes: [
        { id: '1', name: 'Pasta Carbonara', recipe_text: 'Spaghetti, eggs, bacon, cheese', isFavorite: false },
        { id: '2', name: 'Chicken Curry', recipe_text: 'Chicken, curry paste, coconut milk', isFavorite: false },
        { id: '3', name: 'Caesar Salad', recipe_text: 'Lettuce, croutons, Caesar dressing, Parmesan cheese', isFavorite: false }
    ]
};

// Reducer
const reducer = (state: State, action: Action): State => {
    switch (action.type) {
        case 'ADD_RECIPE':
            return {
                ...state,
                recipes: [...state.recipes, action.payload]
            };
        case 'REMOVE_RECIPE':
            return {
                ...state,
                recipes: state.recipes.filter(recipe => recipe.id !== action.payload)
            };
        case 'TOGGLE_FAVORITE':
            return {
                ...state,
                recipes: state.recipes.map(recipe =>
                    recipe.id === action.payload ? { ...recipe, isFavorite: !recipe.isFavorite } : recipe
                )
            };
        default:
            return state;
    }
};

// Kontekst
export const RecipeContext = createContext<{ 
    state: State; 
    dispatch: React.Dispatch<Action> }>({
    
    state: initialState,
    dispatch: () => null
});

// Provider
export const RecipeProvider = ({ children } : {children : React.ReactNode}) => {
    const [state, dispatch] = useReducer(reducer, initialState);

    return (
        <RecipeContext.Provider value={{ state, dispatch }}>
            {children}
        </RecipeContext.Provider>
    );
};
