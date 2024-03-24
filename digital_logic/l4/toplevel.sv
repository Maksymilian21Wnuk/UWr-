


module shifter(input signed[7:0] i, input[3:0] n,
               input ar, lr, rol, output signed[7:0] o);
  
  assign o = ar ? (lr ? i <<< n : i >>> n) : (lr ? i << n : i >> n);
  
  
endmodule
