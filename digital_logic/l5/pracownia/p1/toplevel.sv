// helpful module for comparing two 4 bits numbers
module two_four_bit_compare(input[3:0] i1, i2, output[3:0] o1, o2);
    assign o1 = (i1 < i2) ? i1 : i2;
    assign o2 = (i1 < i2) ? i2 : i1;
endmodule


module four_four_bit_compare(input[15:0] i, output[15:0] o);
    // temporal wires for sorting network
    logic[15:0] t1, t2;

    // apply sorting network using two_four_bit_compare module
    two_four_bit_compare u1(i[3:0], i[11:8], t1[3:0], t1[11:8]);
    two_four_bit_compare u2(i[7:4], i[15:12], t1[7:4], t1[15:12]);
    two_four_bit_compare u3(t1[3:0], t1[7:4], o[3:0], t2[7:4]);
    two_four_bit_compare u4(t1[11:8], t1[15:12], t2[11:8], o[15:12]);
    two_four_bit_compare u5(t2[7:4], t2[11:8], o[7:4], o[11:8]);

endmodule
    
