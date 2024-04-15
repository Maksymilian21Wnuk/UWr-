


module ottf_mult(input[7:0] i, input[1:0] v, output[7:0] o);
  logic three;
  logic s1, s2;

  assign s1 = i << (1 & v[0]);
  assign s2 = s1 << (1 & v[0] & v[1]);

  assign three = v == 2'b10;




endmodule


module shifter(input signed[7:0] i, input[3:0] n,
               input ar, lr, rol, output signed[7:0] o);
  
  assign o = ar ? (lr ? i <<< n : i >>> n) : (lr ? i << n : i >> n);

endmodule
