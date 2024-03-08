module toplevel(output o, input a,b,c,d,x,y); 
    // assign to output based on provided variables
    assign o = d & (x & y) | (c & (x & ~y)) | b & (~x & y) | a & (~x & ~y);
  
endmodule
