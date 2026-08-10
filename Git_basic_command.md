# Git 基础命令备忘

> 用途：保存学习代码 + 两台设备之间同步备份。
> 只要记住下面几条命令就够用了。

---

## 一、每天保存代码（3 步）

改完代码后，在终端依次执行：

```bash
git add .
git commit -m "这次改了什么"
git push
```

- `git add .`：把所有修改的文件都加进来
- `git commit -m "说明"`：存一个点（引号里写中文说明就行）
- `git push`：上传到 GitHub 备份

---

## 二、两台设备之间同步

**关键规则：换设备开工前，先拉取一次最新代码。**

```bash
git pull
```

完整来回流程：

| 步骤 | 设备 A | 设备 B |
|------|--------|--------|
| 开工前 | `git pull` | `git pull` |
| 改完 | `add` + `commit` + `push` | `add` + `commit` + `push` |

---

## 三、查看当前状态

```bash
git status
```

- 显示 `nothing to commit, working tree clean` = 都保存好了
- 显示红色文件名 = 有改动还没 `add`

---

## 四、小提醒

1. **换设备先 `git pull`**，就不会分叉。
2. 如果 `push` 报错提示先拉取，就 `git pull` 再 `git push`。
3. 已经配置过 `pull` 自动合并，偶尔忘了先 pull 也不会报错。
4. 之前分叉的问题已经整理好，以后照上面流程做就行。

---

## 五、新设备配置方法（换电脑/重装系统时用）

第一次在新设备上使用这个仓库，按下面顺序做一遍：

**① 安装 git**（Linux 用 apt，macOS 用 brew，Windows 官网下载）

```bash
sudo apt install git
```

**② 配置用户名和邮箱**（每台新设备都要配一次，否则无法提交）

```bash
git config --global user.name "星河"
git config --global user.email "2384966921@qq.com"
```

**③ 克隆仓库**（把代码下载到这台设备）

```bash
git clone https://github.com/YOCA-520/LearnCode.git
cd LearnCode
```

**④ 设置自动合并**（防止以后分叉报错，和旧设备保持一致）

```bash
git config pull.rebase false
```

**⑤ 之后就和以前一样用了**：`git pull` → 改代码 → `add` + `commit` + `push`

> **小提醒**：新设备第一次 `push` 时，提示输密码的地方**不是填 GitHub 登录密码**，而是填 **Personal Access Token（个人访问令牌）**。在 GitHub 网站 → Settings → Developer settings → Personal access tokens 里生成一个，复制粘贴即可。
