char* month_name(int N){ //RETURN NAME OF N-th MONTH
	
	static char* NAME[] = {
		"ILLEGAL MONTH", "JANUARY", "FEBRUARY", "MARCH", "APRIL",
		"MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", 
		"NOVEMBER", "DECEMBER" };
		
	return ((N < 1 || N >12)? NAME[0] : NAME[N]);
}
		