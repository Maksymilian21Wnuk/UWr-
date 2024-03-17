
module toplevel(output o, input [3:0] i);
    // solved using k-map
    // some temporal variables to get readability
    logic l1 = !i[0] && i[1] && i[3];
    logic l2 = i[0] && !i[2] && i[3];
    logic l3 = i[0] && i[1] && !i[3];
    logic l4 = i[0] && !i[1] && i[2];
    logic l5 = !i[0] && i[1] && i[2];
    logic l6 = !i[1] && i[2] && i[3];
    logic l7 = i[0] && i[1] && !i[2];
    logic l8 = i[1] && i[2] && !i[3];
    logic l9 = i[0] && i[2] && !i[3];
    logic l10 = i[1] && !i[2] && i[3];
    logic l11 = !i[0] && i[2] && i[3];
    logic l12 = i[0] && !i[1] && i[3];
    assign o = l1 || l2 || l3 || l4 || l5 || l6 || l7 || l8 || l9 || l10 || l11 || l12;
endmodule
