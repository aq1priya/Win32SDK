using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ManagedServicesForInterop
{
	//Define IMath Interface
	public interface IMath
	{
		int MultiplicationValue { get; set; }
		int DivisionValue {get; set; }
		int MultiplicationOfTwoIntegers(int num1, int num2);
		int DivisionOfTwoIntegers(int num1, int num2);
	}//end interface IMath
	
	[ClassInterface(ClassInterfaceType.AutoDispatch)]
	public class Math: IMath
	{
		public int MultiplicationValue{get;set;}
		public int DivisionValue{get;set;}
		public Math()
		{
			//empty
		}
		
		public int MultiplicationOfTwoIntegers(int num1, int num2)
		{
			MultiplicationValue = num1 * num2;
			MessageBox.Show("Miltiplication Of Two Integers :" + MultiplicationValue);
			return MultiplicationValue;
		}
		
		public int DivisionOfTwoIntegers(int num1, int num2)
		{
			DivisionValue = num1/num2;
			MessageBox.Show("Division Of Two Integers :" + DivisionValue);
			return DivisionValue;
		}
	}
}