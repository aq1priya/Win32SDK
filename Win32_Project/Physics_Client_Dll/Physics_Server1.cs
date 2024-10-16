using System.Windows.Forms;
using System.Runtime.InteropServices;
using System;

namespace ManagedServerForInterop
{
	//Define IPhysics Interface
	public interface IPhysics
	{
		float CriticalVelocity { get; set; }
		float CalculateCriticalVelocity(float Height);
	}//end interface IPhysics
	
	[ClassInterface(ClassInterfaceType.AutoDispatch)]
	public class Physics: IPhysics
	{
		public float CriticalVelocity{get;set;}
		
		public Physics()
		{
			//empty
		}
		
		public float CalculateCriticalVelocity(float Height)
		{
			float G = (float)(6.67*Math.Pow(10,-11));
			float M = (float)(5.98*Math.Pow(10,24));
			float R = (float)(6400*Math.Pow(10,3));
			Height = Height*1000;
			CriticalVelocity = (float)(Math.Sqrt((G*M)/(R+Height)));
			return CriticalVelocity;
		}
		
	}
}