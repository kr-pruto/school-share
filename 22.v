module sevensegment(num, ot, seg7, digits);         //7-Segment structure
   input [3:0]num;
   input ot; //ot: Ones or Tens
   output [6:0]seg7;
   output [3:0]digits;
   reg [6:0]seg7;
   reg [3:0]digits;
   
   always @(num or ot) begin
      case(ot)
         1'b0 : digits = 4'b1110;  //Activate ones place
         1'b1 : digits = 4'b1101;  //Activate tens place
      endcase
      
      case(num)
         4'b0001 : seg7 = 7'b1111001;  //1
         4'b0010 : seg7 = 7'b0100100;  //2
         4'b0011 : seg7 = 7'b0110000;  //3
         4'b0100 : seg7 = 7'b0011001;  //4
         4'b0101 : seg7 = 7'b0010010;  //5
         4'b0110 : seg7 = 7'b0000010;  //6
         4'b0111 : seg7 = 7'b1111000;  //7
         4'b1000 : seg7 = 7'b0000000;  //8
         4'b1001 : seg7 = 7'b0010000;  //9
         4'b0000 : seg7 = 7'b1000000;  //0
         default : seg7 = 7'b1111111;  
      endcase
   end
endmodule

module stopwatch(CLOCK_100, reset, start, seg, digit);
    input CLOCK_100;
    input reset, start;
    output [6:0] seg;
    output [3:0] digit;
    reg [3:0] reg_d0, reg_d1; //registers to hold the individual counts
    reg [23:0] ticker; //23 bits needed to count up to 5M bits
    reg [20:0] scan_ticker; // ticker for multiplexing the display
    reg current_digit = 0; // to select between ones and tens place
    wire click;
    wire [6:0] seg0, seg1;
    wire [3:0] digit0, digit1;

    localparam [3:0] STUDENT_ID_TEN = 4'd5;
    localparam [3:0] STUDENT_ID_ONE = 4'd7;

    wire [3:0] TARGET_TEN = 4'd4;
    wire [3:0] TARGET_ONE = 4'd7;

    wire is_target = (reg_d1 == TARGET_TEN) && (reg_d0 == TARGET_ONE);

    // the mod 100M clock to generate a tick every 0.1 second
    always @ (posedge CLOCK_100 or posedge reset) begin
        if (reset)
            ticker <= 0;
        else if (ticker == 10000000) // if it reaches the desired max value reset it
            ticker <= 0;
        else if (start && !is_target) // only start if the input is set high
            ticker <= ticker + 1;
    end

    assign click = ((ticker == 10000000) ? 1'b1 : 1'b0); // click to be assigned high every 0.1 second

    always @ (posedge CLOCK_100 or posedge reset) begin
        if (reset) begin
            reg_d0 <= STUDENT_ID_TEN;
            reg_d1 <= STUDENT_ID_ONE;
        end else if (click) begin //increment at every click
            if (reg_d0 == 4'd0) begin //x9 - the 0.1 second digit
                reg_d0 <= 4'd9;
                if (reg_d1 == 4'd0) //99
                    reg_d1 <= 4'd9;
                else
                    reg_d1 <= reg_d1 - 1;
            end else
                reg_d0 <= reg_d0 - 1;
        end
    end

    // Multiplexing logic for the 7-segment display
    always @ (posedge CLOCK_100) begin
        scan_ticker <= scan_ticker + 1;
        if (scan_ticker == 10000) begin // Change digit to display every 1ms
            scan_ticker <= 0;
            current_digit <= ~current_digit;
        end
    end

    // Instantiate sevensegment modules
    sevensegment Seg7_0 (reg_d0, 1'b0, seg0, digit0);
    sevensegment Seg7_1 (reg_d1, 1'b1, seg1, digit1);
    
    // Output assignment based on current digit
    assign seg = current_digit ? seg1 : seg0;
    assign digit = current_digit ? digit1 : digit0;

endmodule
