1. ��ʹ�����ݽṹ���㷨�Ĺ�˼��ԭ����ʵ��Ҫ�㡣
  hashtable������dictionary��bitmap

2. ��ɹ��������������⣬�ų��������Ҫ���̡�ʹ�õķ����ͼ��ɣ��Լ��ο����ϡ�

  * hash function. �õ��˶���ʽhash function�Ϳ�����ȡģ�㷨��
  * �ҳ�����Ϊlen���ַ����ĳ��ִ���������n-len������Ϊlen�����ַ��������μ���hash code����β��ɾ������ʱ�䣩���洢��Ӧ��valueΪ�����ַ���������ʼ�㣬����һ������洢����ʼ������ַ����ĳ��ִ�����times������ʼ��Ϊ0�����һ�����ַ���hash code��Ӧ��value�ǿգ���ô��Ӧ��value��times�������ֵ+1. ��˼����ҵ���������Ϊlen�ĸ������ַ����ĳ��ִ������ȷ������ֵ��
  * �����㷨���������L���ȵ�m�δ�����ôһ������L-1���ȵġ���ˣ������Ӵ����ȵļ�С��������ظ����������Ƿǽ��ġ�����������Ҫ�ҵ�һ�������ȣ���ʹ����ظ��������ڵ���m����С������ô����ȱ�Ȼ������ظ��������ڵ���m����ġ�hiΪn��loΪ1�����ֲ��Ҽ��ɵõ���
  * �õ�������Ⱥ���Ȼ����ó��ȵĸ��ַ����ĳ��ִ������ҵ����г��ִ������ڵ���m�����Ҳ��һ�������������ʼ�㡣Ȼ���ٶԸô��ҳ����Ҳ���ʼ�㡣
  * ���������Խ���ܲ����Ӧ�ö��ø�hash����������ϧûʱ���ˣ���������
3. ʱ��Ϳռ临�ӶȵĹ��㡣

   ����hash��$O(n)$���ܹ�$n$�㣬��Ϊ$O(n\log n)$���ռ临�Ӷ�Ϊ$O(n)$��

4. ����ѡ���������۷�����ʵ��Ч�����Ǻϳ̶ȣ����Ǻ�ʱ��һ������ԭ��

5. ����ѡ�����÷������ر���ӱ����֮����