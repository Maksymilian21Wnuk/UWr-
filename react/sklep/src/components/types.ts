import { GridColDef } from "@mui/x-data-grid";

// type for foods and row cols for datagrid
export type Food = {
    id?: number;
    name: string;
    type: string;
    price: number;
    availability?: boolean;
    quantity: number;
};

export type Foods = {
    rows: Food[];
    setter : React.Dispatch<React.SetStateAction<Food[]>>;
    setOpenRow: React.Dispatch<React.SetStateAction<boolean>>;
};

export type Row_cols = {
    rows : Food[];
    columns: GridColDef[];
};