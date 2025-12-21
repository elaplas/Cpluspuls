1. Use std::lock_guard when:

-You want simple, scope-based locking

-You do not need to unlock manually

-You want minimal overhead

2. Use std::unique_lock when:

-You need flexible locking/unlocking

-You need to lock later (deferred lock)

-You're using std::condition_variable

Feature	                       std::lock_guard	std::unique_lock
Basic use (RAII lock/unlock)	   ✅ Yes	        ✅ Yes
Lock/unlock manually	            ❌ No	        ✅ Yes
Can be moved	                    ❌ No	        ✅ Yes
Locking delayed (deferred)	        ❌ No	        ✅ Yes
Try to acquire (non-blocking)	    ❌ No	        ✅ Yes (try_lock)
Condition variable support	        ❌ No	        ✅ Yes (required)
Overhead	                        Minima Slightly   more (due to flexibility)