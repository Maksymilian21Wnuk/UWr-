import React, { useState } from 'react';
import { DataGrid } from '@mui/x-data-grid';
import { IconButton, Button, Dialog, DialogActions, DialogContent, DialogContentText, DialogTitle, Modal, Box } from '@mui/material';
import DeleteIcon from '@mui/icons-material/Delete';
import { Row_cols} from './types';
import ModalAdd from './ModalAdd';

const MyTable: React.FC<Row_cols> = ({ rows, columns }) => {
    const [newRows, setNewRows] = useState(rows);
    const [deleteId, setDeleteId] = useState<number | null>(null);
    const [open, setOpen] = useState(false);

    const [addRow, setAddRow] = useState(false);

    const handleDeleteClick = (id: number) => {
        setDeleteId(id);
        setOpen(true);
    };

    const handleClose = () => {
        setOpen(false);
    };

    const handleDeleteConfirmation = () => {
        if (deleteId !== null) {
            const updatedRows = newRows.filter(row => row.id !== deleteId);
            setNewRows(updatedRows);
            setOpen(false);
        }
        
    };

    const handleAddRowClose = () => {
        setAddRow(false);
    }

    return (
        <div style={{ height: 1000, width: '100%' }}>
        <Button onClick={() => setAddRow(true)}>
          Add product
        </Button>
        <Modal  
          open={addRow}
          onClose={handleAddRowClose}
          aria-labelledby="modal-modal-title"
          aria-describedby="modal-modal-description">
                <Box sx={{
                    position: 'absolute' as 'absolute',
                    top: '50%',
                    left: '50%',
                    transform: 'translate(-50%, -50%)',
                    width: 400,
                    bgcolor: 'background.paper',
                    border: '2px solid #000',
                    boxShadow: 24,
                    p: 4,
                }}>
                    <ModalAdd rows={newRows} setter={setNewRows} setOpenRow={handleAddRowClose} />
                </Box>
        </Modal>
        

            <DataGrid
                getRowId={(row) => row.id}
                rows={newRows}
                columns={[...columns, {
                    field: 'actions',
                    headerName: 'Actions',
                    width: 100,
                    renderCell: (params) => <IconButton aria-label="delete" color="inherit" onClick={() => handleDeleteClick(params.row.id)}>
                    <DeleteIcon />
                </IconButton>,
                    sortable: false,
                    filterable: false
                }]}
                initialState={{
                    pagination: {
                        paginationModel: { page: 0, pageSize: 10 },
                    },
                }}
                pageSizeOptions={[10, 20, 40]}
            />
            <Dialog
                open={open}
                onClose={handleClose}>
                <DialogTitle id="alert-dialog-title">{"Want to remove?"}</DialogTitle>
                <DialogContent>
                    <DialogContentText id="alert-dialog-description">
                        Are you sure you want to delete this row?
                    </DialogContentText>
                </DialogContent>
                <DialogActions>
                    <Button onClick={handleClose}>No</Button>
                    <Button onClick={handleDeleteConfirmation} autoFocus>Yes</Button>
                </DialogActions>
            </Dialog>
        </div>
    );
}

export default MyTable;
