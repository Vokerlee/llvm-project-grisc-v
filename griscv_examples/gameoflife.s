	.text
	.file	"gameoflife.c"
	.globl	main                            ; -- Begin function main
	.type	main,@function
main:                                   ; @main
; %bb.0:                                ; %entry
	addi	x2, x2, -136
	sd	x1, 128(x2)                     ; 8-byte Folded Spill
	sd	x8, 120(x2)                     ; 8-byte Folded Spill
	addi	x8, x2, 136
	andi	x2, x2, -8
	addi	x10, x0, 0
	sw	x10, 116(x2)
	addi	x11, x0, 1080
	sd	x11, 104(x2)
	addi	x11, x0, 720
	sd	x11, 96(x2)
	addi	x11, x0, 4
	sd	x11, 88(x2)
	addi	x11, x0, 42
	sd	x11, 80(x2)
	addi	x11, x0, 1000
	sd	x11, 72(x2)
	gf	x11
	sd	x11, 64(x2)
	sd	x10, 56(x2)
	ld	x10, 96(x2)
	addi	x10, x10, -1
	sd	x10, 48(x2)
	jal	x0, .LBB0_1
.LBB0_1:                                ; %while.cond
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_3 Depth 2
	ld	x10, 48(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_6
	jal	x0, .LBB0_2
.LBB0_2:                                ; %while.body
                                        ;   in Loop: Header=BB0_1 Depth=1
	ld	x10, 104(x2)
	addi	x10, x10, -1
	sd	x10, 40(x2)
	jal	x0, .LBB0_3
.LBB0_3:                                ; %while.cond2
                                        ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ld	x10, 40(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_5
	jal	x0, .LBB0_4
.LBB0_4:                                ; %while.body4
                                        ;   in Loop: Header=BB0_3 Depth=2
	ld	x10, 88(x2)
	ld	x11, 104(x2)
	ld	x12, 48(x2)
	mul	x11, x11, x12
	ld	x12, 40(x2)
	add	x11, x11, x12
	mul	x10, x10, x11
	sd	x10, 56(x2)
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x11, x10, x11
	addi	x10, x0, 255
	sb	x10, 3(x11)
	ld	x10, 80(x2)
	rand	x10
	andi	x10, x10, 1
	addi	x11, x0, 170
	mul	x10, x10, x11
	ld	x12, 64(x2)
	ld	x11, 56(x2)
	add	x11, x11, x12
	sb	x10, 1(x11)
	ld	x10, 40(x2)
	addi	x10, x10, -1
	sd	x10, 40(x2)
	jal	x0, .LBB0_3
.LBB0_5:                                ; %while.end
                                        ;   in Loop: Header=BB0_1 Depth=1
	ld	x10, 48(x2)
	addi	x10, x10, -1
	sd	x10, 48(x2)
	jal	x0, .LBB0_1
.LBB0_6:                                ; %while.end12
	flush	
	addi	x10, x0, 0
	sd	x10, 32(x2)
	sd	x10, 24(x2)
	jal	x0, .LBB0_7
.LBB0_7:                                ; %while.cond13
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_9 Depth 2
                                        ;       Child Loop BB0_11 Depth 3
                                        ;         Child Loop BB0_13 Depth 4
                                        ;           Child Loop BB0_15 Depth 5
	ld	x10, 72(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_35
	jal	x0, .LBB0_8
.LBB0_8:                                ; %while.body15
                                        ;   in Loop: Header=BB0_7 Depth=1
	ld	x10, 96(x2)
	addi	x10, x10, -1
	sd	x10, 16(x2)
	jal	x0, .LBB0_9
.LBB0_9:                                ; %while.cond18
                                        ;   Parent Loop BB0_7 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_11 Depth 3
                                        ;         Child Loop BB0_13 Depth 4
                                        ;           Child Loop BB0_15 Depth 5
	ld	x10, 16(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_34
	jal	x0, .LBB0_10
.LBB0_10:                               ; %while.body20
                                        ;   in Loop: Header=BB0_9 Depth=2
	ld	x10, 104(x2)
	addi	x10, x10, -1
	sd	x10, 8(x2)
	jal	x0, .LBB0_11
.LBB0_11:                               ; %while.cond23
                                        ;   Parent Loop BB0_7 Depth=1
                                        ;     Parent Loop BB0_9 Depth=2
                                        ; =>    This Loop Header: Depth=3
                                        ;         Child Loop BB0_13 Depth 4
                                        ;           Child Loop BB0_15 Depth 5
	ld	x10, 8(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_33
	jal	x0, .LBB0_12
.LBB0_12:                               ; %while.body25
                                        ;   in Loop: Header=BB0_11 Depth=3
	addi	x10, x0, 0
	sd	x10, 0(x2)
	addi	x10, x0, 3
	sd	x10, 32(x2)
	jal	x0, .LBB0_13
.LBB0_13:                               ; %while.cond26
                                        ;   Parent Loop BB0_7 Depth=1
                                        ;     Parent Loop BB0_9 Depth=2
                                        ;       Parent Loop BB0_11 Depth=3
                                        ; =>      This Loop Header: Depth=4
                                        ;           Child Loop BB0_15 Depth 5
	ld	x10, 32(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_20
	jal	x0, .LBB0_14
.LBB0_14:                               ; %while.body28
                                        ;   in Loop: Header=BB0_13 Depth=4
	addi	x10, x0, 3
	sd	x10, 24(x2)
	jal	x0, .LBB0_15
.LBB0_15:                               ; %while.cond29
                                        ;   Parent Loop BB0_7 Depth=1
                                        ;     Parent Loop BB0_9 Depth=2
                                        ;       Parent Loop BB0_11 Depth=3
                                        ;         Parent Loop BB0_13 Depth=4
                                        ; =>        This Inner Loop Header: Depth=5
	ld	x10, 24(x2)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_19
	jal	x0, .LBB0_16
.LBB0_16:                               ; %while.body31
                                        ;   in Loop: Header=BB0_15 Depth=5
	ld	x10, 88(x2)
	ld	x12, 16(x2)
	ld	x11, 32(x2)
	add	x11, x11, x12
	ld	x12, 96(x2)
	add	x11, x11, x12
	addi	x11, x11, -2
	rem	x11, x11, x12
	ld	x13, 104(x2)
	mul	x11, x11, x13
	ld	x14, 8(x2)
	ld	x12, 24(x2)
	add	x12, x12, x14
	add	x12, x12, x13
	addi	x12, x12, -2
	rem	x12, x12, x13
	add	x11, x11, x12
	mul	x10, x10, x11
	sd	x10, 56(x2)
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x10, x10, x11
	lbu	x10, 1(x10)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_18
	jal	x0, .LBB0_17
.LBB0_17:                               ; %if.then
                                        ;   in Loop: Header=BB0_15 Depth=5
	ld	x10, 0(x2)
	addi	x10, x10, 1
	sd	x10, 0(x2)
	jal	x0, .LBB0_18
.LBB0_18:                               ; %if.end
                                        ;   in Loop: Header=BB0_15 Depth=5
	ld	x10, 24(x2)
	addi	x10, x10, -1
	sd	x10, 24(x2)
	jal	x0, .LBB0_15
.LBB0_19:                               ; %while.end45
                                        ;   in Loop: Header=BB0_13 Depth=4
	ld	x10, 32(x2)
	addi	x10, x10, -1
	sd	x10, 32(x2)
	jal	x0, .LBB0_13
.LBB0_20:                               ; %while.end47
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x10, 88(x2)
	ld	x11, 16(x2)
	ld	x12, 96(x2)
	add	x11, x11, x12
	rem	x11, x11, x12
	ld	x13, 104(x2)
	mul	x11, x11, x13
	ld	x12, 8(x2)
	add	x12, x12, x13
	rem	x12, x12, x13
	add	x11, x11, x12
	mul	x10, x10, x11
	sd	x10, 56(x2)
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x10, x10, x11
	lbu	x10, 1(x10)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_22
	jal	x0, .LBB0_21
.LBB0_21:                               ; %if.then58
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x10, 0(x2)
	addi	x10, x10, -1
	sd	x10, 0(x2)
	jal	x0, .LBB0_22
.LBB0_22:                               ; %if.end60
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x10, 0(x2)
	addi	x11, x0, 3
	bne	x10, x11, .LBB0_26
	jal	x0, .LBB0_23
.LBB0_23:                               ; %if.then62
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x10, x10, x11
	lb	x10, 1(x10)
	addi	x11, x0, 0
	bne	x10, x11, .LBB0_25
	jal	x0, .LBB0_24
.LBB0_24:                               ; %if.then68
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x11, x10, x11
	addi	x10, x0, 170
	sb	x10, 1(x11)
	jal	x0, .LBB0_25
.LBB0_25:                               ; %if.end71
                                        ;   in Loop: Header=BB0_11 Depth=3
	jal	x0, .LBB0_32
.LBB0_26:                               ; %if.else
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x10, 0(x2)
	addi	x11, x0, 2
	bne	x10, x11, .LBB0_28
	jal	x0, .LBB0_27
.LBB0_27:                               ; %if.then74
                                        ;   in Loop: Header=BB0_11 Depth=3
	jal	x0, .LBB0_31
.LBB0_28:                               ; %if.else79
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x10, x10, x11
	lb	x10, 1(x10)
	addi	x11, x0, 0
	beq	x10, x11, .LBB0_30
	jal	x0, .LBB0_29
.LBB0_29:                               ; %if.then85
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x11, 64(x2)
	ld	x10, 56(x2)
	add	x11, x10, x11
	addi	x10, x0, 0
	sb	x10, 1(x11)
	jal	x0, .LBB0_30
.LBB0_30:                               ; %if.end88
                                        ;   in Loop: Header=BB0_11 Depth=3
	jal	x0, .LBB0_31
.LBB0_31:                               ; %if.end89
                                        ;   in Loop: Header=BB0_11 Depth=3
	jal	x0, .LBB0_32
.LBB0_32:                               ; %if.end90
                                        ;   in Loop: Header=BB0_11 Depth=3
	ld	x10, 8(x2)
	addi	x10, x10, -1
	sd	x10, 8(x2)
	jal	x0, .LBB0_11
.LBB0_33:                               ; %while.end92
                                        ;   in Loop: Header=BB0_9 Depth=2
	ld	x10, 16(x2)
	addi	x10, x10, -1
	sd	x10, 16(x2)
	jal	x0, .LBB0_9
.LBB0_34:                               ; %while.end94
                                        ;   in Loop: Header=BB0_7 Depth=1
	flush	
	ld	x10, 72(x2)
	addi	x10, x10, -1
	sd	x10, 72(x2)
	jal	x0, .LBB0_7
.LBB0_35:                               ; %while.end96
	addi	x10, x0, 0
	addi	x2, x8, -136
	ld	x8, 120(x2)                     ; 8-byte Folded Reload
	ld	x1, 128(x2)                     ; 8-byte Folded Reload
	addi	x2, x2, 136
	jalr	x0, 0(x1)
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        ; -- End function
	.ident	"clang version 19.0.0git (https://github.com/Vokerlee/llvm-project-grisc-v.git d0c146b49cd863979237d12f817d6cb6e033821a)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
