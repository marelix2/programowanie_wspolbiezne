#include<linux/module.h>
 #include<linux/list.h>
 #include<linux/slab.h>
 #include<linux/random.h>

 struct example_struct
 {
 int random_value;
 struct list_head list_element;
 };

 static LIST_HEAD(head);

 static int __init listmod_init(void)
 {
 struct example_struct *element;
7 struct list_head *entry;
18 u8 i;
19
20 for(i=0;i<4;i++) {
21 element = (struct example_struct *)
22 kmalloc(sizeof(struct example_struct),GFP_KERNEL);
23 if(!IS_ERR(element)) {
24 get_random_bytes((int *)&element->random_value,
25 sizeof(element->random_value));
26 INIT_LIST_HEAD(&element->list_element);
27 list_add_tail(&element->list_element,&head);
28 }
29 }
30 list_for_each(entry, &head) {
31 element = list_entry(entry, struct example_struct, list_element);
32 pr_notice("Element's value: %u\n",element->random_value);
33 }
34
35 return 0;
36 }
3
37
38 static void __exit listmod_exit(void)
39 {
40 struct example_struct *element, *next;
41
42 list_for_each_entry_safe(element, next, &head, list_element) {
43 list_del(&element->list_element);
44 pr_notice("Element's value: %u\n",element->random_value);
45 kfree(element);
46 }
47 }
48
49 module_init(listmod_init);
50 module_exit(listmod_exit);
51
52 MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
53 MODULE_LICENSE("GPL");
54 MODULE_DESCRIPTION("An exemplary kernel module that demonstrates the usage of a kernel list.");
55 MODULE_VERSION("1.0");