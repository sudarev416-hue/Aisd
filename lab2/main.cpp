import std;
import Class;
int main(){
   LinkedList<int> a(5, 1, 100);
   std::cout << a << "\n";
   a[0]=67;
   a[1]=67;
   a[4]=67;
   // a[2]=67;
   a[3]=67;
   std::cout << a <<"\n";
   a.delete_note(67);
   std::cout << a << "\n";
   return 0;
}
