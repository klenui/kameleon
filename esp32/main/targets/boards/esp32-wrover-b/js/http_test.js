print("in script ok\n");
import http from 'http';

http.get({
  path: 'http://naver.com'
})
.on('response', )