# SDL音频播放流程

* 创建一个回调函数，用于混合音频数据，并放入音频流

* 设置音频参数，调用`SDL_OpenAudio`, 打开音频设备

* 调用`SDL_PauseAudio(0)`, 进行音频回放

* 回放结束后，调用`SDL_CloseAudio()`关闭音频设备


# 相关函数说明

## `SDL_OpenAudio`

将获取Audio设备并将其打开，一个进程只能打开一次，多次打开会报错。打开后，可以对其进行`SDL_PauseAudio`,`SDL_CloseAudio`操作。


## `SDL_PauseAudio`

该函数用于调用打开Audio时设置的回调。


## `SDL_MixAudio`

```
函数原型：
void SDL_MixAudio(Uint8 *dst, Uint8 *src, Uint32 len, int volume);

```

把两个buffer内容叠加起来
