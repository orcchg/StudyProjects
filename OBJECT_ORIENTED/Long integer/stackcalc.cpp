void calculator() {
	stack <double> calc(100);
	double a, b;
	char str[10];
	cout<<"Enter <q> for exit"<<endl;
	do {
		cout<<":";
		scanf("%s", str);
		switch (str[0]) {
			case '+':
			a=calc.pop();
			b=calc.pop();
			cout<<a+b<<endl;
			calc.push(a+b);
			break;
		case '-':
			a=calc.pop();
			b=calc.pop();
			cout<<b-a<<endl;
			calc.push(b-a);
			break;
		case '*':
			a=calc.pop();
			b=calc.pop();
			cout<<a*b<<endl;
			calc.push(a*b);
			break;
		case '/':
			a=calc.pop();
			b=calc.pop();
			if (!a) {
				cout<<"Error!"<<endl;
				return;
			}
			cout<<b/a<<endl;
			calc.push(b/a);
			break;
		case '.':
			a=calc.pop();
			calc.push(a);
			cout<<"Current value is: ";
			cout<<a<<endl;
			break;
		default:
			calc.push(atof(str)); 
		}
	} while(str[0]!='q'); 
}