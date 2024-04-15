

module gray_code_to_bin(input[31:0] i, output[31:0] o);
    assign o[31] = i[31];
    genvar g;
    for (g=30; g>=0; g=g-1) begin
        assign o[g] = o[g+1] == i[g] ? 1'b0 : 1'b1;
    end


endmodule