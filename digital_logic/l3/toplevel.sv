module four_bit_prediction_sum(input[3:0] a, b, input C0,
                               output[3:0] s);
  assign s[0] = a[0] ^ b[0] ^ C0;
  assign s[1] = a[1] ^ b[1] ^ a[0] & b[0] | a[0] & C0 | b[0] & C0;
  assign s[2] = a[2] ^ b[2] ^ (a[1] & b[1] | a[1] & a[0] & b[0] | a[0] & C0 | b[0] & C0 | b[1] & a[0] & b[0] | a[0] & C0 | b[0] & C0);
  assign s[3] = a[2] & b[2] | a[2] & (a[1] & b[1] | a[1] & a[0] & b[0] | a[0] & C0 | b[0] & C0 | b[1] & a[0] & b[0] | a[0] & C0 | b[0] & C0) | b[2] & (a[1] & b[1] | a[1] & a[0] & b[0] | a[0] & C0 | b[0] & C0 | b[1] & a[0] & b[0] | a[0] & C0 | b[0] & C0);

endmodule



module toplevel(input[15:0] a, b, output[15:0] o); 
  logic p0 = a[0] | b[0];
  logic g0 = a[0] & b[0];
  logic p1 = a[1] | b[1];
  logic g1 = a[1] & b[1];
  logic p2 = a[2] | b[2];
  logic g2 = a[2] & b[2];
  logic p3 = a[3] | b[3];
  logic g3 = a[3] & b[3];
   
  logic G0 = g3 | (p3 & g2) | (p3 & p2 & g1) | (p3 & p2 & p1 & g0);  
  logic P0 = p0 & p1 & p2 & p3;
  logic C0 = G0;
  
  logic p4 = a[4] | b[4];
  logic g4 = a[4] & b[4];
  logic p5 = a[5] | b[5];
  logic g5 = a[5] & b[5];
  logic p6 = a[6] | b[6];
  logic g6 = a[6] & b[6];
  logic p7 = a[7] | b[7];
  logic g7 = a[7] & b[7];

  logic G1 = g7 | (p7 & g6) | (p7 & p6 & g5) | (p7 & p6 & p5 & g4);
  logic P1 = p4 & p5 & p6 & p7;
  logic C1 = G1 | G0 & P0;
  
  logic p8 = a[8] | b[8];
  logic g8 = a[8] & b[8];
  logic p9 = a[9] | b[9];
  logic g9 = a[9] & b[9];
  logic p10 = a[10] | b[10];
  logic g10 = a[10] & b[10];
  logic p11 = a[11] | b[11];
  logic g11 = a[11] & b[11];
  
  logic G2 = g11 | (p11 & g10) | (p11 & p10 & g9) | (p11 & p10 & p9 & g8); 
  logic P2 = p8 & p9 & p10 & p11; 
  logic C2 = G2 | G1 & P2 | G0 & P2 & P1;
  
  four_bit_prediction_sum s1(a[3:0], b[3:0], 0, o[3:0]);
  four_bit_prediction_sum s2(a[7:4], b[7:4], C0, o[7:4]);
  four_bit_prediction_sum s3(a[11:8], b[11:8], C1, o[11:8]);
  four_bit_prediction_sum s4(a[15:12], b[15:12], C2, o[15:12]);
 

endmodule

