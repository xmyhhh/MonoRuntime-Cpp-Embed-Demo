using System;
using System.Runtime.CompilerServices;
namespace ManagedLibrary
{
    public class Component
    {
        //×Ö¶Î
        private IntPtr native_handle = (IntPtr)0;
        
        
        //·½·¨
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Component[] GetComponents();
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static int get_id_Internal(IntPtr native_handle);
        
        
        //ÊôÐÔ
        public int ID
        {
            get
            {
                return get_id_Internal(this.native_handle);
            }
        }
        public int Tag
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }

    public static class Main
    {
        public static void TestComponent()
        {
            Component[] components = Component.GetComponents();
            foreach (Component com in components)
            {
                Console.WriteLine("component id is " + com.ID);
                Console.WriteLine("component tag is " + com.Tag);
            }
        }
    }
}