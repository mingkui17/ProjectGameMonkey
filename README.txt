Made by Phạm Thị Minh Khuê (CN8_KHMT_UET)
_Project môn LTNC_

Game: Fruits Monkey (Hứng hoa quả)
    Cách chơi: 
      + Di chuyển chuột sang trái phải để điều khiển khỉ ăn đồ, mỗi loại đồ tương ứng với số điểm khác nhau.
      + Bạn thua khi khỉ ăn phải boom hoặc để rơi đồ quá số lần cho phép.
      + Ăn hoa quả liên tiếp 10 lần sẽ được cộng thêm số lượt bỏ qua.

UPDATE sau khi chấm:
    1. Đảm bảo ván chơi nào cũng sẽ có boom và hoa quả
	 Giải thích: Mỗi ván e khởi tạo 20 vật rơi ngẫu nhiên và e mặc định cho nó là vật rơi thứ i sẽ là boom,
			và vật rơi thứ 2 là quả chuối.
			
    2. Thay đổi sự khác nhau giữa các level: từ dễ đến khó, tốc độ vật rơi tăng dần và số lượng boom tăng dần
	 Giải thích: 
	    + Easy & Medium: E mặc định cho ván chơi cùng số lượng boom, số boom còn lại tùy thuộc vào việc random.
			     Nhưng do sự khác nhau về tốc độ nên level easy sẽ dễ hơn nhiều dù có số boom mặc định = medium.
	    + Hard: Số boom mặc định nhiều hơn 2 level trước
    3. Thêm luật chơi: Ăn hoa quả liên tiếp 10 lần (không trúng SHIT) sẽ cộng thêm số lần skip

Nguồn tham khảo code:
    Slide bài giảng
    Lazyfoo
    https://phattrienphanmem123az.com/lap-trinh-game-cpp

