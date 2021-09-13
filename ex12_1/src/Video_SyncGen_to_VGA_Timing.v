//Video_SyncGen_to_VGA_Timing

module Video_SyncGen_to_VGA_Timing(
			VGA_B,
			VGA_BLANK_n,
			VGA_CLK,
			VGA_G,
			VGA_HS,
			VGA_R,
			VGA_SYNC_n,
			VGA_VS,
			Video_DEN,
			Video_HD,
			Video_RGB_Out,
			Video_VD,
			Video_CLK
);

///////// VGA ////////
output	[7:0]					VGA_B;
output							VGA_BLANK_n;
output							VGA_CLK;
output	[7:0]					VGA_G;
output							VGA_HS;
output	[7:0]					VGA_R;
output							VGA_SYNC_n;
output							VGA_VS;
///////// Video ////////
input								Video_DEN;
input								Video_HD;
input		[23:0]				Video_RGB_Out;
input								Video_VD;
input								Video_CLK;

assign VGA_B = (Video_DEN==1'b0) ? 8'h0:Video_RGB_Out[23:16];
assign VGA_G = (Video_DEN==1'b0) ? 8'h0:Video_RGB_Out[15:8];
assign VGA_R = (Video_DEN==1'b0) ? 8'h0:Video_RGB_Out[7:0];

assign VGA_HS = Video_HD;
assign VGA_VS = Video_VD;
assign VGA_CLK = ~Video_CLK;

assign VGA_BLANK_n = Video_HD&Video_VD;
assign VGA_SYNC_n = 1'b0;

endmodule
