import java.util.*;

public class Main {
	public static void main(String[] args) {
		try {
			Superclass supper = new Superclass(new Exception());
			System.out.println(supper.get());
		} catch(NullPointerException e) {
			System.out.println("Il riferimento è nullo!");
		}
	}
}

class Superclass {
	private Object obj;

	public Superclass(Object obj) throws NullPointerException {
		if(obj == null)
			throw new NullPointerException();
		this.obj = obj;
	}

	public String get() {
		Class klass = obj.getClass();

		while(klass != Object.class) {
			if(klass.getSuperclass() == Object.class)
				break;
			klass = klass.getSuperclass();
		}
		return klass.getSimpleName();
	}
}
