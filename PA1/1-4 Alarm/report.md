1. ��ʹ�����ݽṹ���㷨�Ĺ�˼��ԭ����ʵ��Ҫ�㡣
  ��������Ҫ������ֲ��Ҽ���ѧ����Ľ���������û�в��ñȽ���������ݽṹ
2. ��ɹ��������������⣬�ų��������Ҫ���̡�ʹ�õķ����ͼ��ɣ��Լ��ο����ϡ�
  ��1�������жϵ���ֱ����һ�࣬���������ʵ�ڸ�����ѧ�оͽ�������֪alarm������Ϊ(0, ay)��(ax, 0)������ֱ�߷���Ϊ��
  	$ay*x+ax*y-ax*ay=0$
  ����point (px, py)��������һ�ֻ࣬Ҫ�ж�����(0, 0)�Ƿ�ͬ�༴�ɡ�Ҳ�������Ǵ���ֱ�߷��̲���ˣ��������ࡣҲ�����ϸ������ʱ��
  	$(ay*px + ax * py - ax*ay)>0$
  ��ʽ�����γ˷������Ա�Ϊ��
  	$px * py - (ax-px)(ay-py) > 0?$
  ��2�����ֲ�������_
  �ҿ�ʼ���õ�Ϊ���ֲ��ҵİ汾C��������ϸ�����࣬�������Ϊ[lo, mi]����֮Ϊ��Ϊ[mi+1, lo]��ֵ��ע�����ֱ��i���ڵ�������i+1. �ʶ�������������Ӧ���������������ֱ�ߵ�+1. �����㷨����lo������--lo.
  �����ҷ��ֵ���ǡ����ֱ���ϵ�ʱ�������㷨�����Ĵ𰸲���ȷ�������ǡ����ֱ����mi�����䲻����࣬hi=mi������������ȥ���õ�hi=lo=mi����󷵻�lo. ����ĿҪ��point������ʱ�����Ҳ࣬Ҳ��Ӧ�÷���lo+1���ʶ����������Ҳ��ò����ӵ��Ƿ�ǡ����ֱ��mi�ϵ��жϣ�����ھͷ���mi+1������
  ��������Ϊ�����㷨�ж�̫�࣬���ǲ��ö��ֲ��ҵİ汾B��Ȼ������ͬ�������⣬��ֻ�ܲ�����֮�ˡ�����

3. ʱ��Ϳռ临�ӶȵĹ��㡣
  ʱ�临�Ӷ�ΪO(logn)����Ϊ�Ƕ��ֲ���
  �ռ临�Ӷ�ΪO(4n)����Ϊ����4��nά����
4. ����ѡ���������۷�����ʵ��Ч�����Ǻϳ̶ȣ����Ǻ�ʱ��һ������ԭ��
5. ����ѡ�����÷������ر���ӱ����֮����